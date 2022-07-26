cls

[Environment]::SetEnvironmentVariable("PATH", $Env:PATH + ";C:\mingw64\bin\;C:\cmake-3.23.2-windows-x86_64\bin\")

ECHO "CHECKING IF GCC IS INSTALLED"
gcc --version
if (-Not ($?))
{
    cls
    ECHO "GCC NOT FOUND!"
    $options = '&Yes', '&No'
    $decision = $Host.UI.PromptForChoice("Install gcc", "Gcc.exe was not found, do you wish to install gcc?", $options, 0)
    if($decision -eq 0)
    { 
        cls
        echo "Installing mingw64 from https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z @ C:\MinGW64"

        Start-BitsTransfer -Source "https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z" -Destination "C:\mingw64.7z"

        echo "Downloaded mingw64.7z"
        Install-Module -Name 7Zip4PowerShell -Force
        Expand-7Zip C:\mingw64.7z -TargetPath C:\
        del C:\mingw64.7z
        echo "Installed mingw64"
    } else {
        echo "build canceled"
        exit
    }

}

ECHO "CHECKING IF CMAKE IS INSTALLED"
cmake --version
if (-Not ($?))
{
    cls
    ECHO "CMAKE NOT FOUND!"
    $options = '&Yes', '&No'
    $decision = $Host.UI.PromptForChoice("Install Cmake", "Cmake.exe was not found, do you wish to install cmake?", $options, 0)
    if($decision -eq 0)
    { 
        cls
        echo "Installing cmake from https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip @ C:\cmake-3.23.2-windows-x86_64"

        Start-BitsTransfer -Source "https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip" -Destination "C:\cmake.zip"

        echo "Downloaded cmake.zip"
        if(Test-Path "C:\cmake-3.23.2-windows-x86_64")
        {
            Remove-Item "C:\cmake-3.23.2-windows-x86_64" -Force -Recurse
        }
        Expand-Archive C:\cmake.zip -DestinationPath C:\  
        del C:\cmake.zip
        echo "Installed cmake"
    } else {
        echo "build canceled"
        exit
    }
}

if (!(Test-Path "Libraries"))
{
    mkdir Libraries
}
if (!(Test-Path "Libraries\include"))
{
    mkdir Libraries\include
}
if (!(Test-Path "Libraries\lib"))
{
    mkdir Libraries\lib
}

if (!(Test-Path "Libraries\include\GLFW"))
{

    echo "COPYING GLFW FILES"
    if (Test-Path ".\tmplib")
    {
        Remove-Item ".\tmplib" -Force -Recurse
        mkdir tmplib
    } else {
        mkdir tmplib
    }

    Copy-Item -Path "../submodules/glfw/" -Destination "tmplib/" -Recurse

    echo "BUILDING GLFW"
    cd tmplib
    cd glfw
    mkdir build
    cd build

    cmake "..\" -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=.\install

    mingw32-make
    mingw32-make install

    echo "COPYING COMPILED FILES"

    cd ../../../

    Copy-Item -Path "./tmplib/glfw/build/install/include/GLFW" -Destination "./Libraries/include/GLFW/" -Recurse
    Copy-Item -Path "./tmplib/glfw/build/install/lib/libglfw3.a" -Destination "./Libraries/lib/" -Recurse

    echo "DELETING OLD FILES"
    
    Remove-Item ".\tmplib" -Force -Recurse

}

if (!(Test-Path "Libraries\include\glm"))
{
    echo "COPYING GLM FILES"
    Copy-Item -Path "../submodules/glm/glm/" -Destination "./Libraries/include/glm/" -Recurse
}

if (!(Test-Path "glad.o"))
{
    echo "COMPILING GLAD"
    g++ -c ..\src\glad\glad.c -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
}

if (!(Test-Path "imgui.o"))
{
    echo "COPYING IMGUI FILES"
    if (Test-Path "..\src\ImGui\")
    {
        Remove-Item "..\src\ImGui\" -Force -Recurse
        mkdir ..\src\ImGui\
    } else {
        mkdir ..\src\ImGui\
    }
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_opengl3.cpp ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_opengl3_loader.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_glfw.h ..\src\ImGui
    copy ..\submodules\imgui\backends\imgui_impl_glfw.cpp ..\src\ImGui
    copy ..\submodules\imgui\*.cpp ..\src\ImGui
    copy ..\submodules\imgui\*.h ..\src\ImGui
    echo "COMPILING IMGUI"
    g++ -c ..\src\ImGui\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
}


echo "STARTING ENGINE COMPILATION"

g++ -c ..\src\TGEP\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Layers\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Windows\OpenGL\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\RenderApi\OpenGL\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Shader\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/


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

echo "ENGINE COMPILATION DONE!"

echo "STARTING COMPILATION OF TEST PROJECT"

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./Libraries/lib/ -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -I./Libraries/include/ -I../src/glad/ -static-libgcc -static-libstdc++

echo "COMPILATION DONE!"


.\sandbox.exe



