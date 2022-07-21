@echo off
cls

if not exist "imgui.o" (
    echo COPYING IMGUI FILES
    mkdir ..\src\ImGui\
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.cpp ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_opengl3_loader.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_glfw.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_glfw.cpp ..\src\ImGui
    copy ..\submodules\imgui\*.cpp ..\src\ImGui
    copy ..\submodules\imgui\*.h ..\src\ImGui
    echo COMPILING IMGUI
    g++ -c ..\src\ImGui\*.cpp
)
if not exist "libglfw3.a" (
    echo BUILDING GLAD 
)

if not exist "glad.o" (
    echo COMPILING GLAD
    g++ -c ..\src\glad\glad.c 
)

echo STARTING ENGINE COMPILATION

set Includes=-I../src/ImGui/ -I../src/TGEP/

g++ -c ..\src\TGEP\*.cpp %Includes%
g++ -c ..\src\TGEP\Layers\*.cpp %Includes%
g++ -c ..\src\TGEP\Windows\OpenGL\*.cpp %Includes%
g++ -c ..\src\TGEP\RenderApi\OpenGL\*.cpp %Includes%
g++ -c ..\src\TGEP\Shader\*.cpp %Includes%


ar rcs libTGEP.a *.o

del Application.o
del Log.o
del Layer.o 
del LayerStack.o
del ImGuiLayer.o
del Input.o
del OpenGLWindow.o
del OpenGLContext.o
del Window.o
del OpenGLShader.o

echo ENGINE COMPILATION DONE!

echo STARTING COMPILATION OF TEST PROJECT

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -static-libgcc -static-libstdc++

echo COMPILATION DONE!



.\sandbox.exe