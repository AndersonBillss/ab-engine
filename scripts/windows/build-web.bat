@echo off
call "%~dp0shared\enter-root-dir.bat" || exit /b 1

python build.py run-web-debug