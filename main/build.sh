#!/bin/sh

set -e

CROSS_COMPILE="arm-linux-gnueabihf-"
if [ "$1"x == "win32"x ]; then
    LVGL_PORT_PLATFORM="win32"
    GCC="gcc"
    GXX="g++"
elif [ "$1"x == "linux"x ]; then
    LVGL_PORT_PLATFORM="linux"
    GCC=$CROSS_COMPILE"gcc"
    GXX=$CROSS_COMPILE"g++"
elif [ "$1"x == ""x ]; then
    echo "Please enter parameters, win32 or linux"
    exit 0
fi

LVGL_TOP_DIR=$PWD/..
LVGL_PLATFORM_DIR=$LVGL_TOP_DIR/$LVGL_PORT_PLATFORM
LVGL_PLATFORM_LIB_DIR=$LVGL_PLATFORM_DIR/lib
LVGL_BUILD_DIR=$LVGL_TOP_DIR/build
LVGL_INCLUDE_DIR=$LVGL_BUILD_DIR/_install/include/lvgl
LVGL_LIB_DIR=$LVGL_BUILD_DIR/_install/lib
LVGL_MAIN_DIR=$PWD

CFLAGS="-Wall -I$LVGL_INCLUDE_DIR -I$LVGL_PLATFORM_DIR"
LDFLAGS="-L$LVGL_BUILD_DIR -llvgl_examples -llvgl_demos -L$LVGL_LIB_DIR -L$LVGL_PLATFORM_LIB_DIR -llvgl"
SRCS=`ls *.c`

case "$LVGL_PORT_PLATFORM" in
"win32")
    CFLAGS="$CFLAGS -mwindows"
    LDFLAGS="$LDFLAGS -lgdi32 -llvgl_win32 --static -DWIN32"
    ;;
"linux")
    CFLAGS="$CFLAGS"
    LDFLAGS="$LDFLAGS -llvgl_linux --static -DLINUX"
    ;;
*)
    echo "unsupported platform !"
    exit 0
    ;;
esac
$GCC -o $LVGL_MAIN_DIR/test $CFLAGS $SRCS $LDFLAGS