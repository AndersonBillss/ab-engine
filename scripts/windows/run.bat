@echo off
setlocal
call "%~dp0shared\load-msvc.bat" || exit /b 1

make run-engine-debug