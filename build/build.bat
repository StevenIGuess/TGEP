cls
@echo off
set Vcvarsall_dir="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build"

echo "SETTING VCVARS"
pushd %Vcvarsall_dir%
call .\vcvarsall.bat x64
if %ERRORLEVEL% NEQ 0 echo "COULD NOT SET VCVARS, PLEASE SET THE vcvarsall_dir IN build.bat"
popd
cls

echo "CHECKING IF CMAKE IS INSTALLED"
cmake --version 
if %ERRORLEVEL% NEQ 0 echo Error "CMAKE IS NOT INSTALLED, PLEASE INSTALL CMAKE" 

if not exist ".\Libraries\" (
    mkdir Libraries
)

if not exist ".\Libraries\include\" (
    mkdir Libraries\include
)

if not exist ".\Libraries\lib\" (
    mkdir Libraries\lib
)

if not exist ".\Libraries\include\GLFW\" (

    echo "COPYING GLFW FILES"
    if exist ".\tmplib\" (
        RD /S /Q .\tmplib\
        mkdir tmplib
    ) else (
        mkdir tmplib
    )

    robocopy /e ../submodules/glfw/ tmplib/glfw/

    echo "BUILDING GLFW"
    cd ./tmplib/glfw
    mkdir build
    cd build

    cmake -G "Visual Studio 17 2022" -A x64  -S ..\ -B "build64"
    cmake --build build64 --config Release
    echo "COPYING COMPILED FILES"

    
    robocopy ./build64/src/Release/ ../../../Libraries/lib/
    cd ../../../
    robocopy /e ./tmplib/glfw/include/GLFW ./Libraries/include/GLFW/ 
    
    echo "DELETING OLD FILES"
    
)

if not exist ".\Libraries\include\asio\" (
    echo "COPYING ASIO FILES"
    robocopy /e ../submodules/asio/asio/include/ ./Libraries/include/
)

if not exist ".\Libraries\include\glm\" (
    echo "COPYING GLM FILES"
    robocopy /e ../submodules/glm/glm/ ./Libraries/include/glm/
)
if not exist ".\glad.obj" (
    echo "COMPILING GLAD"
    cl /Fo /EHsc /c ../src/glad/glad.c /I..\src\glad\ 
)

if not exist ".\stb_image.obj" (
    echo "COMPILING STB_IMAGE"
    cl /Fo /EHsc /c ..\src\stb_image\stb_image.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
)

if not exist ".\imgui.obj" (

    echo "COPYING IMGUI FILES"
    if not exist "..\src\ImGui\" (
        RD /S /Q ..\src\ImGui\
        mkdir ..\src\ImGui\
    ) else (
        mkdir ..\src\ImGui\
    )
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.h ..\src\ImGui 
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.cpp ..\src\ImGui 
    copy ..\submodules\imgui\backends\imgui_impl_opengl3_loader.h ..\src\ImGui 
    copy ..\submodules\imgui\backends\imgui_impl_glfw.h ..\src\ImGui  
    copy ..\submodules\imgui\backends\imgui_impl_glfw.cpp ..\src\ImGui 
    robocopy /e ..\submodules\imgui\ .\src\ImGui\
    echo "COMPILING IMGUI"
    cl /Fo /EHsc /c ..\src\ImGui\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I../src/glad/ /I./Libraries/include/
)

if not exist ".\implot.obj" (
    echo "COPYING IMPLOT FILES"

    if exist "..\src\ImPlot\" (
       RD /S /Q ..\src\ImPlot\
       mkdir ..\src\ImPlot\
    ) else (
        mkdir ..\src\ImPlot\
    )
    robocopy /e ..\submodules\implot\ ..\src\ImPlot
    echo "COMPILING IMPLOT"
    cl /Fo /EHsc /c ..\src\ImPlot\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
)

echo "STARTING ENGINE COMPILATION"

cl /Fo /EHsc /c  ..\src\TGEP\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest
cl /Fo /EHsc /c  ..\src\TGEP\Layers\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest
cl /Fo /EHsc /c  ..\src\TGEP\Windows\OpenGL\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest
cl /Fo /EHsc /c  ..\src\TGEP\Renderer\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest
cl /Fo /EHsc /c  ..\src\TGEP\RenderAPI\OpenGL\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest
cl /Fo /EHsc /c  ..\src\TGEP\Networking\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/ /std:c++latest

lib *.obj /OUT:TGEP.lib

del Application.obj
del Layer.obj 
del LayerStack.obj
del ImGuiLayer.obj
del Input.obj
del OpenGLWindow.obj
del OpenGLContext.obj
del Window.obj
del OpenGLShader.obj
del Renderer.obj
del RendererAPI.obj
del Shader.obj
del VertexArray.obj
del OpenGLBuffer.obj
del OpenGLRendererAPI.obj
del RenderCommand.obj
del Camera.obj

echo "ENGINE COMPILATION DONE!"

echo "STARTING COMPILATION OF TEST PROJECT"

cl /EHsc ..\src\Sandbox\sandbox.cpp .\Libraries\lib\glfw3.lib .\TGEP.lib /I../src/ /I./Libraries/include/ /I../src/glad/ /std:c++latest

echo "COMPILATION DONE!"

echo "COPYING ASSETS"
if not exist "Sandbox/" (
    mkdir Sandbox/
) else (
    RD /S /Q Sandbox/ -Force -Recurse
    mkdir Sandbox/
)
copy .\sandbox.exe .\Sandbox\
copy .\server.exe .\Sandbox\
RD /S /Q .\sandbox.exe
RD /S /Q .\server.exe
robocopy /e ..\src\Sandbox\assets\ .\Sandbox\ -Recurse

pushd .\Sandbox\
.\sandbox.exe
popd ..\
