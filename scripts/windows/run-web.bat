@echo off

call scripts/windows/build-web.bat

echo Running engine at http://localhost:8000/ab_engine.html
call python -m http.server --directory ./build/web-engine 8000

