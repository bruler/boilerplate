project(generic-object-detection)

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
cmake_policy(VERSION 3.4.1)

ENABLE_LANGUAGE(C)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Instruct CMake to run moc and rrc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Apple-specific configuration
set(APPLE_SUPPRESS_X11_WARNING ON)

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Werror -Wall -Wextra -Wno-unused-parameter -pedantic -std=c++11")

### Set libraries' locations
# Set Caffe
set(Caffe_DIR "/home/ubuntu/Libraries/caffe")
set(Caffe_INCLUDE_DIRS "/home/cortana/Libraries/caffe/include")
set(Caffe_LIBRARIES "/usr/lib/x86_64-linux-gnu/libcaffe.so")


# Disable debug output for release builds
if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Minimum version requirements
set(QT_MIN_VERSION "5.5.1")

# Find Qt5
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
             Core
             Qml
             Quick
             Concurrent)

# Find OpenCV 3.1
find_package(OpenCV 3.1.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(PythonLibs REQUIRED)
include_directories( ${PYTHON_INCLUDE_DIRS} )

# Find Boost
FIND_PACKAGE(Boost)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" "/usr/include/python2.7")
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
  FIND_PACKAGE(Boost COMPONENTS filesystem python)
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

# Find CUDA
# FIND_PACKAGE(CUDA REQUIRED)

# Find Caffe
FIND_PACKAGE(Caffe REQUIRED)
IF(Caffe_FOUND)
    MESSAGE(STATUS "Caffe Found")
ELSEIF(NOT Caffe_FOUND)
    MESSAGE(STATUS "Caffe NOT Found")
ENDIF()

if(UNIX)
    if(APPLE)
        set(MACOSX_BUNDLE_INFO_STRING "generic-object-detection")
        set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.mybitchinapp.generic-object-detection")
        set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME}-${PROJECT_VERSION}")
        set(MACOSX_BUNDLE_BUNDLE_NAME "generic-object-detection")
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    else()
        # Assume linux
        # TODO: Install desktop and appdata files
    endif()
elseif(WIN32)
# Nothing to do here
endif()

add_subdirectory(src)
