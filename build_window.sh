#!/bin/sh

set -e

cp $PWD/win32/lv_conf.h $PWD/src/lv_conf.h
rm -rf $PWD/build
mkdir  $PWD/build
cd $PWD/build
cmake -G"Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_INSTALL_PREFIX=$PWD/_install ..
make -j8
make install
cd -

