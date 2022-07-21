mkdir install
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make

SET mypath=%~dp0

findstr /V "CMAKE_INSTALL_PREFIX" CMakeCache.txt > CMakeCache.temp
echo CMAKE_INSTALL_PREFIX:PATH=%mypath%/install >> CMakeCache.temp
del CMakeCache.txt
ren CMakeCache.temp CMakeCache.txt

mingw32-make install