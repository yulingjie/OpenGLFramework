Remove-Item .\build -Recures -Force

cd build
rm -r -fo *
cmake -DCMAKE_TOOLCHAIN_FILE=C:\\Software\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake ..
cd ..