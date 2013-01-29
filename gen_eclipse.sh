#!/bin/bash

ROOT_DIR=$PWD
BUILD_DIR=$PWD/"build"
BUILD_DIR_R=$BUILD_DIR/release
BUILD_DIR_D=$BUILD_DIR/debug

mkdir -p $BUILD_DIR
mkdir -p $BUILD_DIR_R
mkdir -p $BUILD_DIR_D

if [ -d $BUILD_DIR_R ]; then
	if [ -f $BUILD_DIR_R/CMakeCache.txt ]; then
		rm $BUILD_DIR_R/CMakeCache.txt
	fi
fi	

if [ -d $BUILD_DIR_D ]; then
	if [ -f $BUILD_DIR_D/CMakeCache.txt ]; then
		rm $BUILD_DIR_D/CMakeCache.txt
	fi
fi	

echo "[[ Generate Release solution]]"
cd $BUILD_DIR_R
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING="Release" --build $BUILD_DIR_R ../../

echo
echo "[[ Generate Debug solution]]"
cd $BUILD_DIR_D
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING="Debug" --build $BUILD_DIR_D ../../

cd $ROOT_DIR
./version.sh
