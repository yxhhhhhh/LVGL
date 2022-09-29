#!/bin/sh

set -e

cp $PWD/linux/lv_conf.h $PWD/src/lv_conf.h
rm -rf $PWD/build
mkdir  $PWD/build
cd $PWD/build
cmake -G"Unix Makefiles" -DCMAKE_C_COMPILER=arm-linux-gnueabihf-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++ -DCMAKE_INSTALL_PREFIX=$PWD/_install ..
make -j8
make install
cd -

