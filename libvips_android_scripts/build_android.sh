#!/bin/bash

set -e
cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1

echo ./ndk_paths.sh
./ndk_paths.sh
echo ./tools/fetch_all.sh
./tools/fetch_all.sh
echo ./libs/fetch_all.sh
./libs/fetch_all.sh
echo cd scripts
cd scripts
echo ./gettext_tiny_build_android.sh
./gettext_tiny_build_android.sh
#./libintl_lite_build_android.sh
echo ./glib_build_android.sh
./glib_build_android.sh
echo ./autoconf_generic_build_android.sh libexpat "--disable-shared --enable-static"
./autoconf_generic_build_android.sh libexpat "--disable-shared --enable-static"
echo ./autoconf_generic_build_android.sh libexif "--disable-shared --enable-static"
./autoconf_generic_build_android.sh libexif "--disable-shared --enable-static"
echo ./libjpeg_build_android.sh
./libjpeg_build_android.sh
echo ./libpng_build_android.sh
./libpng_build_android.sh
echo CFLAGS=-fno-integrated-as ./autoconf_generic_build_android.sh libde265 "--disable-shared --enable-static --disable-dec265 --disable-sherlock265"
CFLAGS=-fno-integrated-as ./autoconf_generic_build_android.sh libde265 "--disable-shared --enable-static --disable-dec265 --disable-sherlock265"
#CFLAGS=-mfpu=neon ./autoconf_generic_build_android.sh libde265 "--disable-dec265 --disable-sherlock265"
echo ./autoconf_generic_build_android.sh libheif "--disable-static --enable-shared --disable-go --disable-examples --disable-aom --disable-x265 --disable-gdk-pixbuf --disable-rav1e"
./autoconf_generic_build_android.sh libheif "--disable-static --enable-shared --disable-go --disable-examples --disable-aom --disable-x265 --disable-gdk-pixbuf --disable-rav1e"
echo ./autoconf_generic_build_android.sh libwebp "--disable-shared --enable-static"
./autoconf_generic_build_android.sh libwebp "--disable-shared --enable-static"
echo ./libvips_build_android.sh
./libvips_build_android.sh
#./missing_symbols_fix_build_android.sh
