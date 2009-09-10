/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: 2009-05-26 17:32:07 +0200 (Tue, 26 May 2009) $
Version:   $Revision: 17418 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef MITKGPUVOLUMEMAPPER3D_H_HEADER_INCLUDED
#define MITKGPUVOLUMEMAPPER3D_H_HEADER_INCLUDED

#include "mitkCommon.h"
#include "mitkBaseVtkMapper3D.h"
#include "mitkBaseRenderer.h"
#include "mitkImage.h"
#include <vtkVolumeProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlane.h>
#include <vtkImplicitPlaneWidget.h>
#include <vtkImageMask.h>
#include <vtkMitkVolumeTextureMapper3D.h>

#include <vector>
#include <set>

class vtkAssembly;
class vtkVolumeRayCastMapper;
class vtkFixedPointVolumeRayCastMapper;
class vtkVolumeTextureMapper2D;
class vtkVolumeMapper;
class vtkVolume;
class vtkObject;
class vtkImageShiftScale;
class vtkImageChangeInformation;
class vtkLODProp3D;
class vtkImageResample;
class vtkCubeSource;
class vtkPolyDataMapper;
class vtkActor;


namespace mitk {

  /************************************************************************/
  /* Properties that influence the mapper are:
  *
  * - \b "level window": for the level window of the volume data
  * - \b "LookupTable" : for the lookup table of the volume data
  * - \b "TransferFunction" (mitk::TransferFunctionProperty): for the used transfer function of the volume data
  ************************************************************************/

//##Documentation
//## @brief Vtk-based mapper for VolumeData
//##
//## @ingroup Mapper
class MITKEXT_CORE_EXPORT GPUVolumeMapper3D : public BaseVtkMapper3D
{
public:
  mitkClassMacro(GPUVolumeMapper3D, BaseVtkMapper3D);

  itkNewMacro(Self);

  virtual const mitk::Image* GetInput();

  virtual void ApplyProperties(vtkActor* actor, mitk::BaseRenderer* renderer);

  virtual void EnableMask();
  virtual void DisableMask();
  Image::Pointer GetMask();
  bool SetMask(const Image* mask);
  virtual void UpdateMask();

  static void SetDefaultProperties(mitk::DataTreeNode* node, mitk::BaseRenderer* renderer = NULL, bool overwrite = false);

  /** Returns true if this Mapper currently allows for Level-of-Detail rendering.
   * This reflects whether this Mapper currently invokes StartEvent, EndEvent, and
   * ProgressEvent on BaseRenderer. */
  virtual bool IsLODEnabled( BaseRenderer *renderer = NULL ) const;

protected:


  GPUVolumeMapper3D();


  virtual ~GPUVolumeMapper3D();

  virtual void GenerateData(mitk::BaseRenderer* renderer);

  void CreateDefaultTransferFunctions();

  void UpdateTransferFunctions( mitk::BaseRenderer *renderer );

  void SetPreferences();

  void SetClippingPlane(vtkRenderWindowInteractor* interactor);
  void DelClippingPlane();

  vtkImageShiftScale* m_ImageCast;
  vtkImageChangeInformation* m_UnitSpacingImageFilter;
  vtkVolumeProperty* m_VolumePropertyLow;
  vtkVolumeProperty* m_VolumePropertyMed;
  vtkVolumeProperty* m_VolumePropertyHigh;
  vtkMitkVolumeTextureMapper3D* m_T2DMapper;
  vtkFixedPointVolumeRayCastMapper* m_HiResMapper;
  vtkImageResample* m_Resampler;
  
  vtkVolume * m_VolumeLOD;
  
  vtkCubeSource *m_BoundingBox;
  vtkPolyDataMapper *m_BoundingBoxMapper;
  vtkActor *m_BoundingBoxActor;

  vtkAssembly *m_Prop3DAssembly;

  vtkPlane* m_ClippingPlane;
  vtkImplicitPlaneWidget* m_PlaneWidget;

  vtkImageData *m_Mask;
  vtkImageMask *m_ImageMaskFilter;

  vtkPiecewiseFunction *m_DefaultOpacityTransferFunction;
  vtkPiecewiseFunction *m_DefaultGradientTransferFunction;
  vtkColorTransferFunction *m_DefaultColorTransferFunction;

  int m_LowResID;
  int m_MedResID;
  int m_HiResID;
  bool m_PlaneSet;
  double m_PlaneNormalA;
  double m_PlaneNormalB;
  double m_PlaneNormalC;

  std::set< vtkRenderWindow * > m_RenderWindowInitialized;

};

} // namespace mitk

#endif /* MITKVOLUMEDATAVTKMAPPER3D_H_HEADER_INCLUDED */