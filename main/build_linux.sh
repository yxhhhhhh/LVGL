#!/bin/sh

set -e

LVGL_BUILD_DIR=$PWD/../build/
LVGL_DIR=$PWD/..
SRCS=`ls *.c`

arm-linux-gnueabihf-gcc -Wall -static -DLINUX -I$LVGL_BUILD_DIR/_install/include/lvgl -I$LVGL_DIR/ -I$LVGL_DIR/linux/ -L$LVGL_BUILD_DIR -L$LVGL_DIR/linux/lib/ -L$LVGL_BUILD_DIR/_install/lib $SRCS -llvgl_examples -llvgl_demos -llvgl -llinux -lpthread -o test

