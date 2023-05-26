
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)
project("vipdroid")

add_subdirectory(src)

find_package(PkgConfig REQUIRED)

find_library(log-lib log)                # Search for the NDK library

pkg_search_module(VIPS REQUIRED vips-cpp)   # libvips

include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/glib-2.0/")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/gio-unix-2.0/")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/libexif")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/libheif")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/libpng16")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/include/webp")
include_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/lib/glib-2.0/include/")

link_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/lib/")
link_directories("../../../../libvips_android_scripts/build/armv7a-linux-androideabi/install/usr/local/lib/glib-2.0/")
target_link_libraries( # Specifies the target library.
                       vipdroid

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
