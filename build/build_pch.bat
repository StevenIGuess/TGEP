@echo off
set PATH=%PATH%;C:\mingw64\bin\;C:\cmake-3.23.2-windows-x86_64\bin\

set Includes=-I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/

g++ ..\src\TGEP\pch.h %Includes%

