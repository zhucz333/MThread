@echo off

set buildDir=%~dp0\..\build_64_Debug

if not exist %buildDir%	(md %buildDir%)

cd /d %buildDir%

echo Setup Visual Studio 2017 64 bit Debug Solution in %cd%

cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 Win64" .. 

pause