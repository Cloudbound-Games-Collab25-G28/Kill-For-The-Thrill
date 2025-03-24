@echo off

set ROOTDIR=%~dp0
set ROOTDIR=%ROOTDIR:~0,-1%

set PROJECT=CloudboundGames
set PROJECT_DIR=%ROOTDIR%\%PROJECT%
set UPROJECT_PATH=%PROJECT_DIR%\%PROJECT%.uproject



set /p UE4_DIR=<%ROOTDIR%\UE_path.txt

set BUILD_PATH=%UE4_DIR%\Engine\Build\BatchFiles\Build.bat

call "%BUILD_PATH%" %PROJECT%Editor Win64 Development "%UPROJECT_PATH%" -waitmutex -NoHotReload