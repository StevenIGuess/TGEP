Install-Module -Name 7Zip4PowerShell -Force

(New-Object Net.WebClient).DownloadFile('https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z', 'C:\mingw64.7z');

Expand-7Zip C:\mingw64.7z -TargetPath C:\

del C:\mingw64.7z



(New-Object Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip', 'C:\cmake.zip');

Expand-Archive C:\cmake.zip -DestinationPath C:\ -Force 

del C:\cmake.zip
