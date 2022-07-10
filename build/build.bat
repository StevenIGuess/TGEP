@echo off
cls

echo STARTING ENGINE COMPILATION

g++ -c ..\src\TGEP\Application.cpp  ..\src\TGEP\Log.cpp
g++ -shared -o TGEP.dll Application.o Log.o

del Application.o
del Log.o

echo ENGINE COMPILATION DONE!

echo STARTING COMPILATION OF TEST PROJECT

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -I ..\src

echo COMPILATION DONE!

.\sandbox.exe