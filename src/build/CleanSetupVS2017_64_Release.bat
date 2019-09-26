@echo off

set buildDir=%~dp0\..\build_64_Release

if exist %buildDir%	(rd /s /Q %buildDir% && md %buildDir%)

%~dp0\SetupVS2017_64_Release.bat