@echo off
call "%~dp0shared\load-msvc.bat" || exit /b 1
call "%~dp0shared\enter-root-dir.bat" || exit /b 1

python build.py run-engine-debug