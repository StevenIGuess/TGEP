@echo off

set Includes=-I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/

g++ ..\src\TGEP\pch.h %Includes%

