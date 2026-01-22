@echo off

call emcmake cmake -S . -B build/web-engine -G Ninja
call cmake --build  build/web-engine --verbose