#!/bin/bash
workdir=$(cd $(dirname $0); pwd)

buildDir=$workdir/../build_64_Debug

if [ -d $buildDir ];then
	rm -rf $buildDir
fi

bash $workdir/SetupLinux_64_Debug.sh