#
# OpenCV
#

SET(OpenCV_DEPENDS)
  
  SET(OpenCV_enabling_variable OpenCV_LIBRARY)
  
  SET(proj OpenCV)
  SET(proj_DEPENDENCIES)
  
  SET(OpenCV_DEPENDS ${proj})
  execute_process(COMMAND ${GIT_EXECUTABLE} remote show "${git_protocol}://github.com/b3c/OpenCV.git"
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                  RESULT_VARIABLE RESULT)
  
  SET(ep_base "${MAF_EXTERNAL_BUILD_DIR}")
  SET_PROPERTY(DIRECTORY PROPERTY EP_BASE ${ep_base})
  
  SET(ep_install_dir ${ep_base}/Install)
  SET(ep_build_dir ${ep_base}/Build)
  SET(ep_source_dir ${ep_base}/Source)
  #SET(ep_parallelism_level)
  SET(ep_build_shared_libs ON)
  SET(ep_build_testing OFF)
  
  #SET(revision_tag 0cbd682)
if(APPLE)
  set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvmgcc42")
endif(APPLE)

IF(RESULT)
  IF(NOT DEFINED OpenCV_DIR)
    #MESSAGE("Adding project:${proj}")
    
    ExternalProject_Add(${proj}
      DOWNLOAD_DIR "${ep_build_dir}/${proj}"
      CMAKE_GENERATOR ${gen}
      INSTALL_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DCMAKE_XCODE_ATTRIBUTE_GCC_VERSION=${CMAKE_XCODE_ATTRIBUTE_GCC_VERSION}
        -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
        -DWITH_FFMPEG:BOOL=FALSE
        -DBUILD_NEW_PYTHON_SUPPORT:BOOL=FALSE
        -DBUILD_DOXYGEN_DOCS:BOOL=FALSE
        -DBUILD_DOXYGEN_EXAMPLES:BOOL=FALSE
        -DBUILD_DOXYGEN_TESTS:BOOL=FALSE
        -DBUILD_DOXYGEN_PACKAGE:BOOL=FALSE
        -DBUILD_DOXYGEN_WITH_CUDA:BOOL=FALSE
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(OpenCV_DIR ${ep_build_dir}/${proj})
    
    # Since OpenCV is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    include(CMake/mafMacroEmptyExternalProject.cmake)
    mafMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()

ELSE(RESULT)
  IF(NOT DEFINED OpenCV_DIR)
    #MESSAGE("Adding project:${proj}")
    
    ExternalProject_Add(${proj}
      GIT_REPOSITORY "${git_protocol}://github.com/b3c/OpenCV.git"
      GIT_TAG "origin/master"
      #GIT_TAG ${revision_tag}
      CMAKE_GENERATOR ${gen}
      INSTALL_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DCMAKE_XCODE_ATTRIBUTE_GCC_VERSION=${CMAKE_XCODE_ATTRIBUTE_GCC_VERSION}
        -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
        -DWITH_FFMPEG:BOOL=FALSE 
        -DBUILD_NEW_PYTHON_SUPPORT:BOOL=FALSE
        -DBUILD_DOXYGEN_DOCS:BOOL=FALSE
        -DBUILD_DOXYGEN_EXAMPLES:BOOL=FALSE
        -DBUILD_DOXYGEN_TESTS:BOOL=FALSE
        -DBUILD_DOXYGEN_PACKAGE:BOOL=FALSE
        -DBUILD_DOXYGEN_WITH_CUDA:BOOL=FALSE
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(OpenCV_DIR ${ep_build_dir}/${proj})
    
    # Since OpenCV is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    include(CMake/mafMacroEmptyExternalProject.cmake)
    mafMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()

ENDIF(RESULT)
  SET(${OpenCV_enabling_variable}_INCLUDE_DIRS OpenCV_INCLUDE_DIRS)
  SET(${OpenCV_enabling_variable}_FIND_PACKAGE_CMD OpenCV)
    


