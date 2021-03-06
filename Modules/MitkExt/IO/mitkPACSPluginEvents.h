/*=========================================================================
 
Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision: 14120 $
 
Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.
 
=========================================================================*/

#ifndef mitkPACSPluginEventshincluded
#define mitkPACSPluginEventshincluded

#include <itkObject.h>
#pragma GCC visibility push(default)
#include <itkEventObject.h>
#pragma GCC visibility pop

namespace mitk
{
  #pragma GCC visibility push(default)
  itkEventMacro( PluginEvent, itk::AnyEvent );
  itkEventMacro( PluginStudySelected, PluginEvent );
  itkEventMacro( PluginLightBoxCountChanged, PluginEvent );
  itkEventMacro( PluginAbortPACSImport, PluginEvent );
  #pragma GCC visibility pop
}

#endif

