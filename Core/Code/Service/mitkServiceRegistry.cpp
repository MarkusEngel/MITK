/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <iterator>

#include "mitkServiceRegistry_p.h"
#include "mitkServiceFactory.h"
#include "mitkServiceRegistry_p.h"
#include "mitkServiceRegistrationPrivate.h"
#include "mitkModulePrivate.h"
#include "mitkCoreModuleContext_p.h"

#include <mitkLogMacros.h>

#include "itkMutexLockHolder.h"


namespace mitk {

typedef itk::MutexLockHolder<ServiceRegistry::MutexType> MutexLocker;

std::size_t HashServiceRegistration::operator()(const ServiceRegistration& s) const
{
  return reinterpret_cast<std::size_t>(s.d);
}


struct ServiceRegistrationComparator
{
  bool operator()(const ServiceRegistration& a, const ServiceRegistration& b) const
  {
    return a < b;
  }
};

ServiceProperties ServiceRegistry::CreateServiceProperties(const ServiceProperties& in,
                                                           const std::list<std::string>& classes,
                                                           long sid)
{
  static long nextServiceID = 1;
  ServiceProperties props(in);

  if (!classes.empty())
  {
    props.insert(std::make_pair(ServiceConstants::OBJECTCLASS(), classes));
  }

  props.insert(std::make_pair(ServiceConstants::SERVICE_ID(), sid != -1 ? sid : nextServiceID++));

  return props;
}

ServiceRegistry::ServiceRegistry(CoreModuleContext* coreCtx)
  : core(coreCtx)
{

}

ServiceRegistry::~ServiceRegistry()
{
  Clear();
}

void ServiceRegistry::Clear()
{
  services.clear();
  serviceRegistrations.clear();
  classServices.clear();
  core = 0;
}

ServiceRegistration ServiceRegistry::RegisterService(ModulePrivate* module,
                                                     const std::list<std::string>& classes,
                                                     itk::LightObject* service,
                                                     const ServiceProperties& properties)
{
  if (service == 0)
  {
    throw std::invalid_argument("Can't register 0 as a service");
  }

  // Check if service implements claimed classes and that they exist.
  for (std::list<std::string>::const_iterator i = classes.begin();
       i != classes.end(); ++i)
  {
    if (i->empty())
    {
      throw std::invalid_argument("Can't register as null class");
    }

    if (!(dynamic_cast<ServiceFactory*>(service)))
    {
      if (!CheckServiceClass(service, *i))
      {
        std::string msg;
        std::stringstream ss(msg);
        ss << "Service class " << service->GetNameOfClass() << " is not an instance of "
               << (*i) << ". Maybe you forgot to export the RTTI information for the interface.";
        throw std::invalid_argument(msg);
      }
    }
  }

  ServiceRegistration res(module, service,
                          CreateServiceProperties(properties, classes));
  {
    MutexLocker lock(mutex);
    services.insert(std::make_pair(res, classes));
    serviceRegistrations.push_back(res);
    for (std::list<std::string>::const_iterator i = classes.begin();
         i != classes.end(); ++i)
    {
      std::list<ServiceRegistration>& s = classServices[*i];
      std::list<ServiceRegistration>::iterator ip =
          std::lower_bound(s.begin(), s.end(), res, ServiceRegistrationComparator());
      s.insert(ip, res);
    }
  }

  ServiceReference r = res.GetReference();
  ServiceListeners::ServiceListenerEntries listeners;
  module->coreCtx->listeners.GetMatchingServiceListeners(r, listeners);
  module->coreCtx->listeners.ServiceChanged(listeners,
                                            ServiceEvent(ServiceEvent::REGISTERED, r));
  return res;
}

void ServiceRegistry::UpdateServiceRegistrationOrder(const ServiceRegistration& sr,
                                                     const std::list<std::string>& classes)
{
  MutexLocker lock(mutex);
  for (std::list<std::string>::const_iterator i = classes.begin();
       i != classes.end(); ++i)
  {
    std::list<ServiceRegistration>& s = classServices[*i];
    std::remove(s.begin(), s.end(), sr);
    s.insert(std::lower_bound(s.begin(), s.end(), sr, ServiceRegistrationComparator()), sr);
  }
}

bool ServiceRegistry::CheckServiceClass(itk::LightObject* , const std::string& ) const
{
  //return service->inherits(cls.toAscii());
  // No possibility to check inheritance based on string literals.
  return true;
}

void ServiceRegistry::Get(const std::string& clazz,
                          std::list<ServiceRegistration>& serviceRegs) const
{
  MutexLocker lock(mutex);
  MapClassServices::const_iterator i = classServices.find(clazz);
  if (i != classServices.end())
  {
    serviceRegs = i->second;
  }
}

ServiceReference ServiceRegistry::Get(ModulePrivate* module, const std::string& clazz) const
{
  MutexLocker lock(mutex);
  try
  {
    std::list<ServiceReference> srs;
    Get_unlocked(clazz, "", module, srs);
    MITK_INFO << "get service ref " << clazz << " for module "
             << module->info.name << " = " << srs.size() << " refs";

    if (!srs.empty())
    {
      return srs.front();
    }
  }
  catch (const std::invalid_argument& )
  { }

  return ServiceReference();
}

void ServiceRegistry::Get(const std::string& clazz, const std::string& filter,
                          ModulePrivate* module, std::list<ServiceReference>& res) const
{
  MutexLocker lock(mutex);
  Get_unlocked(clazz, filter, module, res);
}

void ServiceRegistry::Get_unlocked(const std::string& clazz, const std::string& filter,
                          ModulePrivate* /*module*/, std::list<ServiceReference>& res) const
{
  std::list<ServiceRegistration>::const_iterator s;
  std::list<ServiceRegistration>::const_iterator send;
  std::list<ServiceRegistration> v;
  LDAPExpr ldap;
  if (clazz.empty())
  {
    if (!filter.empty())
    {
      ldap = LDAPExpr(filter);
      LDAPExpr::ObjectClassSet matched;
      if (ldap.GetMatchedObjectClasses(matched))
      {
        v.clear();
        for(LDAPExpr::ObjectClassSet::const_iterator className = matched.begin();
            className != matched.end(); ++className)
        {
          MapClassServices::const_iterator i = classServices.find(*className);
          if (i != classServices.end())
          {
            std::copy(i->second.begin(), i->second.end(), std::back_inserter(v));
          }
        }
        if (!v.empty())
        {
          s = v.begin();
          send = v.end();
        }
        else
        {
          return;
        }
      }
      else
      {
        s = serviceRegistrations.begin();
        send = serviceRegistrations.end();
      }
    }
    else
    {
      s = serviceRegistrations.begin();
      send = serviceRegistrations.end();
    }
  }
  else
  {
    MapClassServices::const_iterator it = classServices.find(clazz);
    if (it != classServices.end())
    {
      s = it->second.begin();
      send = it->second.end();
    }
    else
    {
      return;
    }
    if (!filter.empty())
    {
      ldap = LDAPExpr(filter);
    }
  }

  for (; s != send; ++s)
  {
    ServiceReference sri = s->GetReference();

    if (filter.empty() || ldap.Evaluate(s->d->properties, false))
    {
      res.push_back(sri);
    }
  }
}

void ServiceRegistry::RemoveServiceRegistration(const ServiceRegistration& sr)
{
  MutexLocker lock(mutex);

  const std::list<std::string>& classes = ref_any_cast<std::list<std::string> >(
        sr.d->properties[ServiceConstants::OBJECTCLASS()]);
  services.erase(sr);
  serviceRegistrations.remove(sr);
  for (std::list<std::string>::const_iterator i = classes.begin();
       i != classes.end(); ++i)
  {
    std::list<ServiceRegistration>& s = classServices[*i];
    if (s.size() > 1)
    {
      std::remove(s.begin(), s.end(), sr);
    }
    else
    {
      classServices.erase(*i);
    }
  }
}

void ServiceRegistry::GetRegisteredByModule(ModulePrivate* p,
                                            std::list<ServiceRegistration>& res) const
{
  MutexLocker lock(mutex);

  for (std::list<ServiceRegistration>::const_iterator i = serviceRegistrations.begin();
       i != serviceRegistrations.end(); ++i)
  {
    if (i->d->module == p)
    {
      res.push_back(*i);
    }
  }
}

void ServiceRegistry::GetUsedByModule(Module* p,
                                      std::list<ServiceRegistration>& res) const
{
  MutexLocker lock(mutex);

  for (std::list<ServiceRegistration>::const_iterator i = serviceRegistrations.begin();
       i != serviceRegistrations.end(); ++i)
  {
    if (i->d->IsUsedByModule(p))
    {
      res.push_back(*i);
    }
  }
}

}  // end namespace mitk

