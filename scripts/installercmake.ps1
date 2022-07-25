(New-Object Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip', '.\cmake.zip');

Expand-Archive .\cmake.zip -DestinationPath C:\ -Force 

del .\cmake.zip

..\build\build.bat