@echo off
setlocal
call "%~dp0shared\load-msvc.bat" || exit /b 1

python build.py build-engine-debug