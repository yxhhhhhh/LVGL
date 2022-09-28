#!/bin/sh

set -e

LVGL_BUILD_DIR=$PWD/../build/
LVGL_DIR=$PWD/..
SRCS=`ls *.c`

gcc -Wall -static -mwindows -DWINDOW -I$LVGL_BUILD_DIR/_install/include/lvgl -I$LVGL_DIR/ -I$LVGL_DIR/win32/ -L$LVGL_BUILD_DIR -L$LVGL_DIR/win32/lib/ -L$LVGL_BUILD_DIR/_install/lib $SRCS -llvgl_examples -llvgl_demos -llvgl -lwin -lgdi32 -lpthread -o test
strip test.exe
