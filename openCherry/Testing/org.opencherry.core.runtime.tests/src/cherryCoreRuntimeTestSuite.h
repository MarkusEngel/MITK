/*=========================================================================
 
 Program:   openCherry Platform
 Language:  C++
 Date:      $Date: 2009-09-07 12:05:58 +0200 (Mo, 07 Sep 2009) $
 Version:   $Revision: 18832 $
 
 Copyright (c) German Cancer Research Center, Division of Medical and
 Biological Informatics. All rights reserved.
 See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/


#ifndef CHERRYCORERUNTIMETESTSUITE_H_
#define CHERRYCORERUNTIMETESTSUITE_H_

#include <CppUnit/TestSuite.h>

namespace cherry {

class CoreRuntimeTestSuite : public CppUnit::TestSuite
{
public:

  CoreRuntimeTestSuite();
};

}

#endif /* CHERRYCORERUNTIMETESTSUITE_H_ */