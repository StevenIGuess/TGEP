(New-Object Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip', 'C:\cmake.zip');

Expand-Archive C:\cmake.zip -DestinationPath C:\ -Force 

del C:\cmake.zip