MITK_CREATE_MODULE_TESTS()

IF(BUILD_TESTING AND MODULE_IS_ENABLED) 
	      mitkAddCustomModuleTest("mitkToFImageDownsamplingFilterTest" #name of the test
     "mitkToFImageDownsamplingFilterTest" #call the corresponding test
     "PMDCamCube2_MF0_IT0_20Images_DistanceImage.pic") #input parameter(s)
	      mitkAddCustomModuleTest("mitkToFImageDownsamplingFilterTest" #name of the test
     "mitkToFImageDownsamplingFilterTest" #call the corresponding test
     "PMDCamCube2_MF0_IT0_1Images_DistanceImage.pic") #input parameter(s)
ENDIF(BUILD_TESTING AND MODULE_IS_ENABLED)