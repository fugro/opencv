set(the_description "Fugro Wrapper")

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project("Fugro.OpenCV" VERSION 2.0.0)

# Configure OpenCV
set(BUILD_LIST "core,imgcodecs,imgproc,video,features_2d,flann,calib3d" CACHE STRING "")
option(WITH_WIN32UI "" false)
option(WITH_WEBP "" false)
option(WITH_VTK "" false)
option(WITH_QUIRC "" false)
option(WITH_PROTOBUF "" false)
option(WITH_TIFF "" false)
option(WITH_OPENEXR "" false)
option(WITH_JPEG "" false)
option(WITH_JASPER "" false)
option(WITH_FFMPEG "" false)
option(WITH_ITT "" false)
option(WITH_IPP "" false)
option(WITH_ADE "" false)
option(BUILD_SHARED_LIBS "" false)
option(OPENCV_GENERATE_SETUPVARS "" false)
option(BUILD_WITH_STATIC_CRT "" false)
option(BUILD_TESTS "" false)
option(BUILD_PERF_TESTS "" false)
option(BUILD_opencv_python_tests "" false)
option(BUILD_opencv_python_bindings_generator "" false)
option(BUILD_PACKAGE "" false)
option(BUILD_opencv_ts "" false)
option(BUILD_opencv_ts "" false)
option(BUILD_opencv_videoio "" false)
option(BUILD_opencv_java_bindings_generator "" false)
option(BUILD_opencv_videostab "" false)
option(BUILD_opencv_apps "" false)
option(COMPILE "" false)

add_subdirectory(opencv)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

add_definitions(-D__CRT_SECURE_NO_DEPRECATE)
add_definitions(-D__CRT_NONSTDC_NO_DEPRECATE)
add_definitions(-D__SCL_SECURE_NO_WARNINGS)

# Set source code and includes
set(wrapper_srcs
	src/AssemblyInfo.cpp
	src/Contour.cpp
	src/DoubleArray.cpp
	src/GrabCut.cpp
	src/ImageArray.cpp
	src/Kernel.cpp
	src/MatArray.cpp
	src/MatArrayBase.cpp
)

set(wrapper_include
	src/Contour.h
	src/DoubleArray.h
	src/EllipseInfo.h
	src/Enumerations.h
	src/GrabCut.h
	src/ImageArray.h
	src/Kernel.h
	src/MatArray.h
	src/MatArrayBase.h
	src/OpticalFlowResult.h
	src/Primitives.h
	src/resource.h
)

#set(APP_SRCS ${wrapper_srcs} ${wrapper_include})
set(project_name Fugro.OpenCV)
#project(project_name)

add_library(${project_name} SHARED
	${wrapper_srcs}
	${wrapper_include}
)
set(APP_MODULES opencv_core opencv_imgcodecs opencv_imgproc opencv_video opencv_calib3d opencv_flann opencv_features2d)

foreach(mod ${APP_MODULES})
	include_directories("${OPENCV_MODULE_${mod}_LOCATION}/include")
endforeach()

# Configure includes  
include_directories(${ZLIB_INCLUDE_DIRS} ${LIBPNG_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Configure Linker
target_link_libraries(${project_name} 
			PRIVATE zlib 
			PRIVATE libpng
			PRIVATE opencv_core
			PRIVATE opencv_imgcodecs
			PRIVATE opencv_imgproc
			PRIVATE opencv_calib3d
			PRIVATE opencv_video)
  
target_link_options(${project_name} PRIVATE /NOENTRY )

# Configure Compiler
target_compile_options(${project_name} PRIVATE /clr)
target_compile_options(${project_name} PRIVATE /fp:precise)

string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set( ALL_C_FLAGS "/Gy /doc" )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ALL_C_FLAGS}")
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${REL_C_FLAGS}" )
set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEB_C_FLAGS} -D_DEBUG" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ALL_C_FLAGS}" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${REL_C_FLAGS}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEB_C_FLAGS} -D_DEBUG" )

# Set visual studio properties
set_property(TARGET ${project_name} PROPERTY VS_GLOBAL_ROOTNAMESPACE ${project_name})
set_property(TARGET ${project_name} PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")
set_property(TARGET ${project_name} PROPERTY VS_GLOBAL_CLRSupport "true")
set_property(TARGET ${project_name} PROPERTY VS_CONFIGURATION_CLRSupport "true")
set_property(TARGET ${project_name} PROPERTY COMMON_LANGUAGE_RUNTIME "")

set_target_properties(${project_name} PROPERTIES
                     LINKER_LANGUAGE C
                     VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")

set_property(TARGET ${project_name}  PROPERTY VS_DOTNET_REFERENCES
			"mscorlib"
			"System.Drawing"
			"System.Xaml"
			"System"
			"PresentationCore"
			"System.Data"
			"WindowsBase"
			"System.Xml")

set_property(TARGET ${project_name} PROPERTY VS_GLOBAL_CLRSupport "false")

add_subdirectory(fugrotest)
configure_file("NuGet.Config.in" "${CMAKE_BINARY_DIR}/NuGet.Config")
configure_file("Fugro.OpenCV.nuspec.in" "${CMAKE_BINARY_DIR}/Fugro.OpenCV.nuspec")