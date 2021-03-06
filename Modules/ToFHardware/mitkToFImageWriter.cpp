/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date: 2010-05-27 16:06:53 +0200 (Do, 27 Mai 2010) $
Version:   $Revision: $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include <mitkToFImageWriter.h>
#include <mitkCommon.h>

// itk includes
#include "itksys/SystemTools.hxx"

namespace mitk
{
  ToFImageWriter::ToFImageWriter():m_Extension(".nrrd"),
    m_DistanceImageFileName(), m_AmplitudeImageFileName(), m_IntensityImageFileName(),
    m_NumOfFrames(0), m_DistanceImageSelected(true), m_AmplitudeImageSelected(true),
    m_IntensityImageSelected(true),m_CaptureWidth(200),m_CaptureHeight(200), 
    m_PixelNumber(0), m_ImageSizeInBytes(0), 
    m_ToFImageType(ToFImageWriter::ToFImageType3D)
  {
  }

  ToFImageWriter::~ToFImageWriter()
  {
  }

  void ToFImageWriter::CheckForFileExtension(std::string& fileName)
  {
    std::string baseFilename = itksys::SystemTools::GetFilenameWithoutLastExtension( fileName );
    std::string extension = itksys::SystemTools::GetFilenameLastExtension( fileName );

    if( extension.length() != 0 && extension != this->m_Extension)
    {
      MITK_ERROR << "Wrong file extension! The default extension is " << this->m_Extension.c_str() << ", currently the requested file extension is " << extension.c_str() <<"!";
      this->m_Extension = extension;
    }

    size_t found = fileName.find( this->m_Extension ); // !!! HAS to be at the very end of the filename (not somewhere in the middle)
    if( found == std::string::npos)
    {
      fileName.append(this->m_Extension);
    }
  }

  ToFImageWriter::ToFImageType ToFImageWriter::GetToFImageType()
  {
    return this->m_ToFImageType;
  }

  void ToFImageWriter::SetToFImageType(ToFImageWriter::ToFImageType toFImageType)
  {
    this->m_ToFImageType = toFImageType;
  }

} // end namespace mitk
