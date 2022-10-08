#!/bin/sh

set -e

CROSS_COMPILE="arm-linux-gnueabihf-"
LVGL_PORT_PLATFORM=$1
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
echo $GCC
echo $GXX
LVGL_TOP_DIR=$PWD
LVGL_BUILD_DIR=$LVGL_TOP_DIR/build
LVGL_PLATFORM_DIR=$LVGL_TOP_DIR/$LVGL_PORT_PLATFORM
LVGL_PLATFORM_LIB_DIR=$LVGL_PLATFORM_DIR/lib
LVGL_INSTALL_DIR=$LVGL_BUILD_DIR/_install
LVGL_INCLUDE_DIR=$LVGL_BUILD_DIR/_install/include/lvgl
LVGL_LIB_DIR=$LVGL_BUILD_DIR/_install/lib
LVGL_MAIN_DIR=$PWD/main

case "$1" in
"win32")
    if [ ! -d $LVGL_BUILD_DIR ]; then
        mkdir $LVGL_BUILD_DIR
        cd $LVGL_BUILD_DIR
        cmake -G"Unix Makefiles" -DCMAKE_C_COMPILER=$GCC -DCMAKE_CXX_COMPILER=$GXX -DCMAKE_INSTALL_PREFIX=$LVGL_INSTALL_DIR ..
    fi
    ;;
"linux")
    if [ ! -d $LVGL_BUILD_DIR ]; then
        mkdir $LVGL_BUILD_DIR
        cd $LVGL_BUILD_DIR
        cmake -G"Unix Makefiles" -DCMAKE_C_COMPILER=$GCC -DCMAKE_CXX_COMPILER=$GXX -DCMAKE_INSTALL_PREFIX=$LVGL_INSTALL_DIR ..
    fi
    ;;
clean|distclean)
    rm -rf $LVGL_BUILD_DIR
    rm -rf $LVGL_TOP_DIR/src/lv_conf.h
    rm -rf $LVGL_MAIN_DIR/test.exe
    rm -rf $LVGL_MAIN_DIR/test
    cd $LVGL_TOP_DIR/linux
    make clean
    cd $LVGL_TOP_DIR/win32
    make clean
    exit 0
    ;;
esac
cp $LVGL_PLATFORM_DIR/lv_conf.h $LVGL_TOP_DIR/src/lv_conf.h
cd $LVGL_BUILD_DIR
make -j8
make install
    cd $LVGL_TOP_DIR
    if [ -d "$LVGL_PLATFORM_DIR" ]; then
        cd $LVGL_PLATFORM_DIR 
        make
        cd $LVGL_TOP_DIR
    fi

cd $LVGL_MAIN_DIR && ./build.sh $LVGL_PORT_PLATFORM