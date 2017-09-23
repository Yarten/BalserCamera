cmake_minimum_required(VERSION 2.8)
project(BalserCamera)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   add_definitions(-DCOMPILEDWITHC0X)
   message(STATUS "Using flag -std=c++0x.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# include

include_directories(
/usr/local/include/opencv3_0
/opt/pylon5/include
${PROJECT_SOURCE_DIR}/Camera
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

add_executable(${PROJECT_NAME}
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/Camera/BalserCamera.cpp
${PROJECT_SOURCE_DIR}/Camera/Camera.cpp
${PROJECT_SOURCE_DIR}/Camera/CameraFactory.cpp
${PROJECT_SOURCE_DIR}/Camera/ImageReader.cpp
${PROJECT_SOURCE_DIR}/Camera/OpenCVCamera.cpp
)

target_link_libraries(${PROJECT_NAME}
# opencv
/usr/local/lib/opencv3_0/libopencv_calib3d.so
/usr/local/lib/opencv3_0/libopencv_calib3d.so.3.0
/usr/local/lib/opencv3_0/libopencv_calib3d.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_core.so
/usr/local/lib/opencv3_0/libopencv_core.so.3.0
/usr/local/lib/opencv3_0/libopencv_core.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_features2d.so
/usr/local/lib/opencv3_0/libopencv_features2d.so.3.0
/usr/local/lib/opencv3_0/libopencv_features2d.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_flann.so
/usr/local/lib/opencv3_0/libopencv_flann.so.3.0
/usr/local/lib/opencv3_0/libopencv_flann.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_hal.a
/usr/local/lib/opencv3_0/libopencv_highgui.so
/usr/local/lib/opencv3_0/libopencv_highgui.so.3.0
/usr/local/lib/opencv3_0/libopencv_highgui.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_imgcodecs.so
/usr/local/lib/opencv3_0/libopencv_imgcodecs.so.3.0
/usr/local/lib/opencv3_0/libopencv_imgcodecs.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_imgproc.so
/usr/local/lib/opencv3_0/libopencv_imgproc.so.3.0
/usr/local/lib/opencv3_0/libopencv_imgproc.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_ml.so
/usr/local/lib/opencv3_0/libopencv_ml.so.3.0
/usr/local/lib/opencv3_0/libopencv_ml.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_objdetect.so
/usr/local/lib/opencv3_0/libopencv_objdetect.so.3.0
/usr/local/lib/opencv3_0/libopencv_objdetect.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_photo.so
/usr/local/lib/opencv3_0/libopencv_photo.so.3.0
/usr/local/lib/opencv3_0/libopencv_photo.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_shape.so
/usr/local/lib/opencv3_0/libopencv_shape.so.3.0
/usr/local/lib/opencv3_0/libopencv_shape.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_stitching.so
/usr/local/lib/opencv3_0/libopencv_stitching.so.3.0
/usr/local/lib/opencv3_0/libopencv_stitching.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_superres.so
/usr/local/lib/opencv3_0/libopencv_superres.so.3.0
/usr/local/lib/opencv3_0/libopencv_superres.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_ts.a
/usr/local/lib/opencv3_0/libopencv_videoio.so
/usr/local/lib/opencv3_0/libopencv_videoio.so.3.0
/usr/local/lib/opencv3_0/libopencv_videoio.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_video.so
/usr/local/lib/opencv3_0/libopencv_video.so.3.0
/usr/local/lib/opencv3_0/libopencv_video.so.3.0.0
/usr/local/lib/opencv3_0/libopencv_videostab.so
/usr/local/lib/opencv3_0/libopencv_videostab.so.3.0
/usr/local/lib/opencv3_0/libopencv_videostab.so.3.0.0

# pylonx64
/opt/pylon5/lib64/libbxapi-5.0.9.so
/opt/pylon5/lib64/libbxapi.so
/opt/pylon5/lib64/libFirmwareUpdate_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libGCBase_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libGenApi_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libgxapi-5.0.9.so
/opt/pylon5/lib64/libgxapi.so
/opt/pylon5/lib64/liblog4cpp_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libLog_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libMathParser_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libNodeMapData_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/libpylonbase-5.0.9.so
/opt/pylon5/lib64/libpylonbase.so
/opt/pylon5/lib64/libpylonc-5.0.9.so
/opt/pylon5/lib64/libpylonc.so
/opt/pylon5/lib64/libpylon_TL_bcon-5.0.9.so
/opt/pylon5/lib64/libpylon_TL_bcon.so
/opt/pylon5/lib64/libpylon_TL_camemu-5.0.9.so
/opt/pylon5/lib64/libpylon_TL_camemu.so
/opt/pylon5/lib64/libpylon_TL_gige-5.0.9.so
/opt/pylon5/lib64/libpylon_TL_gige.so
/opt/pylon5/lib64/libpylon_TL_gtc-5.0.9.so
/opt/pylon5/lib64/libpylon_TL_gtc.so
/opt/pylon5/lib64/libpylon_TL_usb-5.0.9.so
/opt/pylon5/lib64/libpylon_TL_usb.so
/opt/pylon5/lib64/libpylonutility-5.0.9.so
/opt/pylon5/lib64/libpylonutility.so
/opt/pylon5/lib64/libuxapi-5.0.9.so
/opt/pylon5/lib64/libuxapi.so
/opt/pylon5/lib64/libXmlParser_gcc_v3_0_Basler_pylon_v5_0.so
/opt/pylon5/lib64/pylon-libusb-1.0.so

# linux
/lib/x86_64-linux-gnu/libpthread.so.0
)
