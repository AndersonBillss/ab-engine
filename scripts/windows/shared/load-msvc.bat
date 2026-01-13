
@echo off
setlocal

REM Ensure I am in the root directory
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%\..\..
cd /d "%ROOT_DIR%"

REM Open MSVC terminal
call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" || (
    echo Failed to initialize MSVC environment
    exit /b 1
)

REM Make sure to use MSVC CMake for building dawn
set "PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;%PATH%"