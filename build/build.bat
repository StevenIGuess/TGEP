@echo off
cls
set PATH=%PATH%;C:\mingw64\bin\;C:\cmake-3.23.2-windows-x86_64\bin\

set Includes=-I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/

if not exist ".\Libraries\lib\libglfw3.a" (

    echo COPYING GLFW FILES
    mkdir tmplib
    robocopy ../submodules/glfw/ tmplib/ /s /e

    echo BUILDING GLFW
    cd tmplib
    mkdir build
    cd build

    cmake .. -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=./install

    mingw32-make
    mingw32-make install

    echo COPYING COMPILED FILES

    cd ../../

    robocopy ./tmplib/build/install/include/GLFW/ ./Libraries/include/GLFW/
    robocopy ./tmplib/build/install/lib ./Libraries/lib

    echo DELETING OLD FILES 
    
    RD /S /Q .\tmplib

)

if not exist ".\Libraries\include\glm\glm.hpp" (

    echo COPYING GLM FILES
    robocopy ../submodules/glm/glm/ ./Libraries/include/glm/ /s /e 
)

if not exist "glad.o" (
    echo COMPILING GLAD
    g++ -c ..\src\glad\glad.c %Includes%
)

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
    g++ -c ..\src\ImGui\*.cpp %Includes%
)


echo STARTING ENGINE COMPILATION

g++ -c ..\src\TGEP\*.cpp %Includes%
g++ -c ..\src\TGEP\Layers\*.cpp %Includes%
g++ -c ..\src\TGEP\Windows\OpenGL\*.cpp %Includes%
g++ -c ..\src\TGEP\RenderApi\OpenGL\*.cpp %Includes%
g++ -c ..\src\TGEP\Shader\*.cpp %Includes%


ar rcs libTGEP.a *.o

del Application.o
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

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./Libraries/lib/ -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -I./Libraries/include/ -I../src/glad/ -static-libgcc -static-libstdc++

echo COMPILATION DONE!


.\sandbox.exe