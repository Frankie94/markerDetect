cmake_minimum_required(VERSION 3.12)
project(markerDetect)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

find_package( OpenCV REQUIRED )
add_executable(markerDetect detector.cpp undistortion.cpp undistortion.h)
target_link_libraries(markerDetect ${OpenCV_LIBS} )
