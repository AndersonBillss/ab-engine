@echo off
setlocal
call "%~dp0shared\load-msvc.bat" || exit /b 1

echo Building Dawn
python build.py dawn-debug-setup