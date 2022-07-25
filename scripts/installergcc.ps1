Install-Module -Name 7Zip4PowerShell -Force

(New-Object Net.WebClient).DownloadFile('https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z', '.\mingw64.7z');

Expand-7Zip .\mingw64.7z -TargetPath C:\

del mingw64.7z

