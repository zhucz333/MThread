@echo off

set buildDir=%~dp0\..\build_32_Debug

if not exist %buildDir%	(md %buildDir%)

cd /d %buildDir%

echo Setup Visual Studio 2017 32 bit Debug Solution in %cd%

cmake -DUSE_32BITS=ON -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15" .. 

pause