#!/bin/bash

workdir=$(cd $(dirname $0); pwd)

buildDir=$workdir/../build_64_Debug

if [ ! -d $buildDir ];then
	mkdir -p $buildDir
fi

cd $buildDir

echo Setup Linux 64 bit Debug Solution in $(pwd)

cmake -DCMAKE_BUILD_TYPE=Debug ..


