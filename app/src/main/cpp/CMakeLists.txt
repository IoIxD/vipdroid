
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)
project("vipdroid")

add_library(vipdroid SHARED vipdroid.cpp)

find_package(PkgConfig REQUIRED)

find_library(log-lib log)                # Search for the NDK library

pkg_search_module(VIPS REQUIRED vips-cpp)   # libvips

if (VIPS_FOUND)
    message (STATUS "VIPS_INCLUDE_DIRS=${VIPS_INCLUDE_DIRS}")
    message (STATUS "VIPS_LIBRARIES=${VIPS_LIBRARIES}")
    message (STATUS "VIPS_LIBRARY_DIRS=${VIPS_LIBRARY_DIRS}")
    include_directories(${VIPS_INCLUDE_DIRS})
    link_directories(${VIPS_LIBRARY_DIRS})

    target_link_libraries(vipdroid vips)
else()
    message (FATAL_ERROR "libvips not found")
endif()



target_link_libraries( # Specifies the target library.
                       vipdroid

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
