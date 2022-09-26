#!/bin/sh

set -e

LVGL_INSTALL_DIR=$PWD/../build/_install
SRCS=`ls *.c`

gcc -Wall -static -mwindows -I$LVGL_INSTALL_DIR/include/lvgl -L$LVGL_INSTALL_DIR/lib -L$PWD/../build $SRCS -llvgl_examples -llvgl_demos -llvgl -lgdi32 -lpthread -o test
strip test.exe
