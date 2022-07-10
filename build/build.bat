@echo off
cls

g++ -c -o TGEP.o ..\src\TGEP\Application.cpp 
g++ -shared -o TGEP.dll TGEP.o

del TGEP.o

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -I ..\src


.\sandbox.exe