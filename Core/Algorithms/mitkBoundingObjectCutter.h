#ifndef BOUNDINGOBJECTCUTTER_H_HEADER_INCLUDED_C10B22CD
#define BOUNDINGOBJECTCUTTER_H_HEADER_INCLUDED_C10B22CD

#include "mitkCommon.h"

#include "mitkBoundingObject.h"
//#include "mitkEllipsoid.h"

#include <mitkImageToImageFilter.h>

#include "itkImage.h"
#include <itkImageFileWriter.h>

#include "itkImageToImageFilter.h"

#include <itkRegionOfInterestImageFilter.h>
#include "itkImageRegionIteratorWithIndex.h"
#include "itkConfidenceConnectedImageFilter.h"
#include <itkMultiplyImageFilter.h>


namespace mitk {

//##Documentation
//## @brief Cuts an Bounding Objectout of an mitk Image
//## @ingroup Process
//## 
//## Input Parameters are a mitk::BoundingObject and optionally an mitk::Image
//## if no mitk::Image is provided, the resulting image will have INSIDEVALUE as pixelvalue on inside voxels, 
//## otherwise it will have the pixelvalue of the input image.
//## Voxels on the outside of the BoundingObject will have a pixelvalue of OUTSIDEVALUE
/**
  *  \todo What Image resolution/spacing should be used, if no input image is given?
  */
class BoundingObjectCutter : public ImageToImageFilter
{
public:
  typedef short PixelType;
  typedef itk::Image<PixelType, 3> ItkImageType;
  typedef itk::RegionOfInterestImageFilter<ItkImageType, ItkImageType> ItkRegionOfInterestFilterType;
  typedef ItkRegionOfInterestFilterType::InputImageRegionType ItkRegionType;
  typedef itk::ImageRegionIteratorWithIndex< ItkImageType > ItkImageIteratorType;
  typedef itk::ImageFileWriter<ItkImageType> ItkImageWriter;

  typedef itk::ImageToImageFilter<ItkImageType, ItkImageType> ImageToImageFilterType;

  typedef itk::ConfidenceConnectedImageFilter<ItkImageType, ItkImageType> ConnectedFilterType;
  typedef  itk::MultiplyImageFilter< ItkImageType, ItkImageType, ItkImageType > MultiplyImageFilterType;

  mitkClassMacro(BoundingObjectCutter, ImageToImageFilter);
  itkNewMacro(Self);

  virtual void GenerateOutputInformation();

  virtual void GenerateData();
  

//  virtual void SetBoundingObject(mitk::Ellipsoid* _arg);
//  virtual const mitk::Ellipsoid* GetBoundingObject();

  itkSetObjectMacro(BoundingObject, mitk::BoundingObject);
  itkGetObjectMacro(BoundingObject, mitk::BoundingObject);

  itkSetMacro(InsideValue,  mitk::BoundingObjectCutter::PixelType);
  itkGetMacro(InsideValue,  mitk::BoundingObjectCutter::PixelType);
  itkSetMacro(OutsideValue, mitk::BoundingObjectCutter::PixelType);
  itkGetMacro(OutsideValue, mitk::BoundingObjectCutter::PixelType);
  itkSetMacro(UseInsideValue, bool);
  itkGetMacro(UseInsideValue, bool);
  itkBooleanMacro(UseInsideValue);

  itkSetMacro(UseRegionGrower, bool);
  itkGetMacro(UseRegionGrower, bool);
  itkBooleanMacro(UseRegionGrower);

  itkSetClampMacro(ConfidenceFactor, float, 0.0, 10.0);
  itkGetMacro(ConfidenceFactor, float);
  
  itkSetObjectMacro(SegmentationFilter, ImageToImageFilterType);
  itkGetObjectMacro(SegmentationFilter, ImageToImageFilterType);

  //ItkImageType::Pointer m_ItkImage;
protected:
  BoundingObjectCutter();
  virtual ~BoundingObjectCutter();

  mitk::BoundingObject::Pointer m_BoundingObject;
  PixelType m_InsideValue;
  PixelType m_OutsideValue;
  bool m_UseInsideValue;
  bool m_UseRegionGrower;
  float m_ConfidenceFactor;
  ImageToImageFilterType::Pointer m_SegmentationFilter;

};

} // namespace mitk

#endif /* BOUNDINGOBJECTCUTTER_H_HEADER_INCLUDED_C10B22CD */
