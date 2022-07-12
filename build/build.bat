@echo off
cls

echo STARTING ENGINE COMPILATION

if exist glad.o (
    g++ -c ..\src\TGEP\Application.cpp ..\src\TGEP\Log.cpp ..\src\TGEP\Window.cpp ..\src\TGEP\Layer.cpp ..\src\TGEP\LayerStack.cpp -I..\src\TGEP
) else (
    g++ -c ..\src\TGEP\Application.cpp ..\src\TGEP\Log.cpp ..\src\TGEP\Window.cpp ..\src\TGEP\Layer.cpp ..\src\TGEP\LayerStack.cpp ..\src\TGEP\glad.c -I..\src\TGEP
)

g++ -shared -o TGEP.dll Application.o Log.o Window.o Layer.o LayerStack.o glad.o -lopengl32 -lglfw3 -lgdi32

del Application.o
del Log.o
del Window.o
del Layer.o 
del LayerStack.o

echo ENGINE COMPILATION DONE!

echo STARTING COMPILATION OF TEST PROJECT

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -I ..\src

echo COMPILATION DONE!



.\sandbox.exe