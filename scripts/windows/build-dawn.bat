@echo off
setlocal
call "%~dp0shared\load-msvc.bat" || exit /b 1

echo Building Dawn
make dawn-debug-setup