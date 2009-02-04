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


#ifndef QMITKDEFAULTPERSPECTIVE_H_
#define QMITKDEFAULTPERSPECTIVE_H_

#include <cherryIPerspectiveFactory.h>

#include "mitkQtAppDll.h"

struct MITK_QT_APP QmitkDefaultPerspective : public cherry::IPerspectiveFactory
{
  QmitkDefaultPerspective();
  void CreateInitialLayout(cherry::IPageLayout::Pointer layout);

};

#endif /* QMITKDEFAULTPERSPECTIVE_H_ */
