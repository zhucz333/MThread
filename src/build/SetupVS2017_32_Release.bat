@echo off

set buildDir=%~dp0\..\build_32_Release

if not exist %buildDir%	(md %buildDir%)

cd /d %buildDir%

echo Setup Visual Studio 2017 32 bit Release Solution in %cd%

cmake -DUSE_32BITS=ON -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15" .. 

pause