cls
@echo off

:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
    IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"

:: change to Libraries/lib/libglfw3.a
if not exist "libglfw3.a" (
    echo COPYING GLFW FILES
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

    robocopy ./tmplib/build/install/include/GLFW/ ./Libraries/include
    robocopy ./tmplib/build/install/lib ./Libraries/lib

    echo DELETING OLD FILES 

    :: delete the stupid folder


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
    g++ -c ..\src\ImGui\*.cpp
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