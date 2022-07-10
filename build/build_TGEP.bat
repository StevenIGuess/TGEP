@echo off
g++ -c -o TGEP.o ..\src\TGEP\Test.cpp 
g++ -shared -o TGEP.dll TGEP.o

del TGEP.o