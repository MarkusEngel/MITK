/*=========================================================================
 
 Program:   openCherry Platform
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

#include "cherryOpenCherryTestDriver.h"

#include "internal/cherryTestRegistry.h"

#include <CppUnit/TestRunner.h>

namespace cherry
{

OpenCherryTestDriver::OpenCherryTestDriver(const std::vector<
    ITestDescriptor::Pointer>& descriptors,
    bool uitests,
    const std::string& testName,
    bool wait) :
  descriptors(descriptors), uitests(uitests), testName(testName), wait(wait)
{

}

int OpenCherryTestDriver::Run()
{
  CppUnit::TestRunner runner;

  unsigned int testCounter = 0;
  for (std::vector<ITestDescriptor::Pointer>::iterator i = descriptors.begin(); i
      != descriptors.end(); ++i)
  {
    ITestDescriptor::Pointer descr(*i);
    if (descr->IsUITest() == uitests)
    {
      CppUnit::Test* test = descr->CreateTest();
      runner.addTest(descr->GetId(), test);
      ++testCounter;
    }
  }

  if (testCounter == 0)
  {
    std::cout << "No " << (uitests ? "UI " : "") << "tests registered."
        << std::endl;
    return 0;
  }

  std::vector<std::string> args;
  args.push_back("OpenCherryTestDriver");
  if (testName.empty())
    args.push_back("-all");
  else
    args.push_back(testName);
  if (wait)
    args.push_back("-wait");

  return runner.run(args) ? 0 : 1;
}

int OpenCherryTestDriver::Run(const std::string& pluginId, bool uitests)
{
  TestRegistry testRegistry;
  const std::vector<ITestDescriptor::Pointer>& tests = testRegistry.GetTestsForId(
      pluginId);

  OpenCherryTestDriver driver(tests, uitests);
  return driver.Run();
}

}