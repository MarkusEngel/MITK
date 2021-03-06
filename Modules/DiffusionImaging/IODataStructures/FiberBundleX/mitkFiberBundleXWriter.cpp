/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: 2008-12-10 18:05:13 +0100 (Mi, 10 Dez 2008) $
Version:   $Revision: 15922 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "mitkFiberBundleXWriter.h"
#include <tinyxml.h>

const char* mitk::FiberBundleXWriter::XML_GEOMETRY = "geometry";

const char* mitk::FiberBundleXWriter::XML_MATRIX_XX = "xx";

const char* mitk::FiberBundleXWriter::XML_MATRIX_XY = "xy";

const char* mitk::FiberBundleXWriter::XML_MATRIX_XZ = "xz";

const char* mitk::FiberBundleXWriter::XML_MATRIX_YX = "yx";

const char* mitk::FiberBundleXWriter::XML_MATRIX_YY = "yy";

const char* mitk::FiberBundleXWriter::XML_MATRIX_YZ = "yz";

const char* mitk::FiberBundleXWriter::XML_MATRIX_ZX = "zx";

const char* mitk::FiberBundleXWriter::XML_MATRIX_ZY = "zy";

const char* mitk::FiberBundleXWriter::XML_MATRIX_ZZ = "zz";

const char* mitk::FiberBundleXWriter::XML_ORIGIN_X = "origin_x";

const char* mitk::FiberBundleXWriter::XML_ORIGIN_Y = "origin_y";

const char* mitk::FiberBundleXWriter::XML_ORIGIN_Z = "origin_z";

const char* mitk::FiberBundleXWriter::XML_SPACING_X = "spacing_x";

const char* mitk::FiberBundleXWriter::XML_SPACING_Y = "spacing_y";

const char* mitk::FiberBundleXWriter::XML_SPACING_Z = "spacing_z";

const char* mitk::FiberBundleXWriter::XML_SIZE_X = "size_x";

const char* mitk::FiberBundleXWriter::XML_SIZE_Y = "size_y";

const char* mitk::FiberBundleXWriter::XML_SIZE_Z = "size_z";

const char* mitk::FiberBundleXWriter::XML_FIBER_BUNDLE = "fiber_bundle";

const char* mitk::FiberBundleXWriter::XML_FIBER = "fiber";

const char* mitk::FiberBundleXWriter::XML_PARTICLE = "particle";

const char* mitk::FiberBundleXWriter::XML_ID = "id";

const char* mitk::FiberBundleXWriter::XML_POS_X = "pos_x";

const char* mitk::FiberBundleXWriter::XML_POS_Y = "pos_y";

const char* mitk::FiberBundleXWriter::XML_POS_Z = "pos_z";

const char* mitk::FiberBundleXWriter::XML_NUM_FIBERS = "num_fibers";

const char* mitk::FiberBundleXWriter::XML_NUM_PARTICLES = "num_particles";

const char* mitk::FiberBundleXWriter::XML_FIBER_BUNDLE_FILE = "fiber_bundle_file" ;

const char* mitk::FiberBundleXWriter::XML_FILE_VERSION = "file_version" ;

const char* mitk::FiberBundleXWriter::VERSION_STRING = "0.1" ;

const char* mitk::FiberBundleXWriter::ASCII_FILE = "ascii_file" ;

const char* mitk::FiberBundleXWriter::FILE_NAME = "file_name" ;

mitk::FiberBundleXWriter::FiberBundleXWriter()
    : m_FileName(""), m_FilePrefix(""), m_FilePattern(""), m_Success(false)
{
    this->SetNumberOfRequiredInputs( 1 );
}


mitk::FiberBundleXWriter::~FiberBundleXWriter()
{}


void mitk::FiberBundleXWriter::GenerateData()
{
  MITK_INFO << "Writing fiber bundle";
  m_Success = false;
  InputType* input = this->GetInput();
  if (input == NULL)
  {
      itkWarningMacro(<<"Sorry, input to FiberBundleXWriter is NULL!");
      return;
  }
  if ( m_FileName == "" )
  {
      itkWarningMacro( << "Sorry, filename has not been set!" );
      return ;
  }

//  std::string ext = itksys::SystemTools::GetFilenameLastExtension(m_FileName);
//  ext = itksys::SystemTools::LowerCase(ext);

//  if (ext == ".fib")
//  {
//    /* direct linked includes of mitkFiberBundleX DataStructure */
//    
//        mitk::Geometry3D* geometry = input->GetGeometry();
//
//    TiXmlDocument documentXML;
//    TiXmlDeclaration* declXML = new TiXmlDeclaration( "1.0", "", "" ); // TODO what to write here? encoding? etc....
//    documentXML.LinkEndChild( declXML );
//
//    TiXmlElement* mainXML = new TiXmlElement(mitk::FiberBundleXWriter::XML_FIBER_BUNDLE_FILE);
//    mainXML->SetAttribute(mitk::FiberBundleXWriter::XML_FILE_VERSION,  mitk::FiberBundleXWriter::VERSION_STRING);
//    documentXML.LinkEndChild(mainXML);
//
//    TiXmlElement* geometryXML = new TiXmlElement(mitk::FiberBundleXWriter::XML_GEOMETRY);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_XX, geometry->GetMatrixColumn(0)[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_XY, geometry->GetMatrixColumn(0)[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_XZ, geometry->GetMatrixColumn(0)[2]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_YX, geometry->GetMatrixColumn(1)[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_YY, geometry->GetMatrixColumn(1)[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_YZ, geometry->GetMatrixColumn(1)[2]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_ZX, geometry->GetMatrixColumn(2)[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_ZY, geometry->GetMatrixColumn(2)[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_MATRIX_ZZ, geometry->GetMatrixColumn(2)[2]);
//
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_ORIGIN_X, geometry->GetOrigin()[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_ORIGIN_Y, geometry->GetOrigin()[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_ORIGIN_Z, geometry->GetOrigin()[2]);
//
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SPACING_X, geometry->GetSpacing()[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SPACING_Y, geometry->GetSpacing()[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SPACING_Z, geometry->GetSpacing()[2]);
//
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SIZE_X, input->GetBounds()[0]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SIZE_Y, input->GetBounds()[1]);
//    geometryXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_SIZE_Z, input->GetBounds()[2]);
//
//    mainXML->LinkEndChild(geometryXML);
//
//    TiXmlElement* FiberBundleXXML = new TiXmlElement(mitk::FiberBundleXWriter::XML_FIBER_BUNDLE);
//    FiberBundleXXML->SetAttribute(mitk::FiberBundleXWriter::XML_NUM_FIBERS, tractContainer->size());
//    int numParticles = 0;
//    for (int i=0; i<tractContainer->Size(); i++)
//    {
//      ContainerTractType::Pointer tract = tractContainer->GetElement(i);
//      TiXmlElement* fiberXML = new TiXmlElement(mitk::FiberBundleXWriter::XML_FIBER);
//      fiberXML->SetAttribute(mitk::FiberBundleXWriter::XML_ID, i);
//      fiberXML->SetAttribute(mitk::FiberBundleXWriter::XML_NUM_PARTICLES, tract->Size());
//      numParticles += tract->Size();
//      for (int j=0; j<tract->Size(); j++)
//      {
//        TiXmlElement* particleXML = new TiXmlElement(mitk::FiberBundleXWriter::XML_PARTICLE);
//        ContainerPointType p = tract->GetElement(j);
//        particleXML->SetAttribute(mitk::FiberBundleXWriter::XML_ID, j);
//        particleXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_POS_X, p[0]);
//        particleXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_POS_Y, p[1]);
//        particleXML->SetDoubleAttribute(mitk::FiberBundleXWriter::XML_POS_Z, p[2]);
//        fiberXML->LinkEndChild(particleXML);
//      }
//      FiberBundleXXML->LinkEndChild(fiberXML);
//    }
//    FiberBundleXXML->SetAttribute(mitk::FiberBundleXWriter::XML_NUM_PARTICLES, numParticles);
//    mainXML->LinkEndChild(FiberBundleXXML);
//
//    documentXML.SaveFile( m_FileName );
//
//    m_Success = true;
//
//    MITK_INFO << "Fiber bundle written";
//
//  }else if (ext == ".vfib" || ext == ".vtk") {
//    vtkPolyDataWriter* writer = vtkPolyDataWriter::New();
//    writer->SetInput(input->GeneratePolydata());
//    writer->SetFileName(m_FileName.c_str());
//    writer->SetFileTypeToASCII();
//    writer->Write();
//
//    m_Success = true;
//    MITK_INFO << "Fiber bundle written as polydata";
//  }

}


void mitk::FiberBundleXWriter::SetInputFiberBundleX( InputType* diffVolumes )
{
    this->ProcessObject::SetNthInput( 0, diffVolumes );
}


mitk::FiberBundleX* mitk::FiberBundleXWriter::GetInput()
{
    if ( this->GetNumberOfInputs() < 1 )
    {
        return NULL;
    }
    else
    {
        return dynamic_cast<InputType*> ( this->ProcessObject::GetInput( 0 ) );
    }
}


std::vector<std::string> mitk::FiberBundleXWriter::GetPossibleFileExtensions()
{
  std::vector<std::string> possibleFileExtensions;
  possibleFileExtensions.push_back(".fib");
  possibleFileExtensions.push_back(".vfib");
  possibleFileExtensions.push_back(".vtk");
  return possibleFileExtensions;
}
