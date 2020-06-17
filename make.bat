echo off
del /F /S /Q build 
if not exist build (mkdir build)
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=C:\\Software\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake ..
cd ..