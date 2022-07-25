@echo off
[Environment]::SetEnvironmentVariable('PATH', ${env:path} + ';C:\mingw64\bin\', 'Machine')

set Includes=-I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/

g++ ..\src\TGEP\pch.h %Includes%

