SET(SRC_CPP_FILES
  cherryMessageTest.cpp
  cherryObjectTest.cpp
  cherryOSGiCoreTestSuite.cpp
  cherrySmartPointerTest.cpp
  cherryWeakPointerTest.cpp
)

SET(INTERNAL_CPP_FILES
  
)

SET(CPP_FILES manifest.cpp)

foreach(file ${SRC_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})