#!/bin/sh

mkdir bin
mkdir build
cd build
rm CMakeCache.txt
cmake ..
make

