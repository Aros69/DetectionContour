cmake_minimum_required(VERSION 3.13)
project(TP1_AnalyseImage)

set(CMAKE_BINARY_DIR "CMakeFiles")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_SOURCE_DIR "src")


#include(CMake/buildOpenCv.cmake)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("src")

add_executable(TP1.exe main.cpp
        src/utils/MatrixFilter.cpp src/utils/MatrixFilter.h
        src/Computations.cpp src/Computations.h src/utils/Matrix.cpp src/utils/Matrix.h)
target_link_libraries(TP1.exe ${OpenCV_LIBS})

add_executable(OpenCvImgDisplay.exe src/imageDisplay.cpp)
target_link_libraries(OpenCvImgDisplay.exe ${OpenCV_LIBS})

#add_executable(OpenCvWebcam.exe src/webcam.cpp)
#target_link_libraries(OpenCvWebcam.exe ${OpenCV_LIBS})

#add_executable(FirstProgram.exe src/FirstProgram/main.cpp
#        src/FirstProgram/Webcam.cpp
#        src/FirstProgram/Webcam.h
#        src/FirstProgram/BackgroundFiltering.cpp
#        src/FirstProgram/BackgroundFiltering.h
#        libs2/opencv/include/ )
#target_link_libraries(FirstProgram.exe ${OpenCV_LIBS})
