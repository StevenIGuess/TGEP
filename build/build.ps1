Clear-Host

[Environment]::SetEnvironmentVariable("PATH", $Env:PATH + ";C:\mingw64\bin\;C:\cmake-3.23.2-windows-x86_64\bin\")

Write-Output "CHECKING IF GCC IS INSTALLED"
gcc --version
if (-Not ($?))
{
    Clear-Host
    Write-Output "GCC NOT FOUND!"
    $options = '&Yes', '&No'
    $decision = $Host.UI.PromptForChoice("Install gcc", "Gcc.exe was not found, do you wish to install gcc?", $options, 0)
    if($decision -eq 0)
    { 
        Clear-Host
        Write-Output "Installing mingw64 from https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z @ C:\MinGW64"

        Start-BitsTransfer -Source "https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z" -Destination "C:\mingw64.7z"

        Write-Output "Downloaded mingw64.7z"
        Install-Module -Name 7Zip4PowerShell -Force
        Expand-7Zip C:\mingw64.7z -TargetPath C:\
        Remove-Item C:\mingw64.7z
        Write-Output "Installed mingw64"
    } else {
        Write-Output "build canceled"
        exit
    }

}

Write-Output "CHECKING IF CMAKE IS INSTALLED"
cmake --version
if (-Not ($?))
{
    Clear-Host
    Write-Output "CMAKE NOT FOUND!"
    $options = '&Yes', '&No'
    $decision = $Host.UI.PromptForChoice("Install Cmake", "Cmake.exe was not found, do you wish to install cmake?", $options, 0)
    if($decision -eq 0)
    { 
        Clear-Host
        Write-Output "Installing cmake from https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip @ C:\cmake-3.23.2-windows-x86_64"

        Start-BitsTransfer -Source "https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip" -Destination "C:\cmake.zip"

        Write-Output "Downloaded cmake.zip"
        if(Test-Path "C:\cmake-3.23.2-windows-x86_64")
        {
            Remove-Item "C:\cmake-3.23.2-windows-x86_64" -Force -Recurse
        }
        Expand-Archive C:\cmake.zip -DestinationPath C:\  
        Remove-Item C:\cmake.zip
        Write-Output "Installed cmake"
    } else {
        Write-Output "build canceled"
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

    Write-Output "COPYING GLFW FILES"
    if (Test-Path ".\tmplib")
    {
        Remove-Item ".\tmplib" -Force -Recurse
        mkdir tmplib
    } else {
        mkdir tmplib
    }

    Copy-Item -Path "../submodules/glfw/" -Destination "tmplib/" -Recurse

    Write-Output "BUILDING GLFW"
    Set-Location tmplib
    Set-Location glfw
    mkdir build
    Set-Location build

    cmake "..\" -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=.\install

    mingw32-make
    mingw32-make install

    Write-Output "COPYING COMPILED FILES"

    Set-Location ../../../

    Copy-Item -Path "./tmplib/glfw/build/install/include/GLFW" -Destination "./Libraries/include/GLFW/" -Recurse
    Copy-Item -Path "./tmplib/glfw/build/install/lib/libglfw3.a" -Destination "./Libraries/lib/" -Recurse

    Write-Output "DELETING OLD FILES"
    
    Remove-Item ".\tmplib" -Force -Recurse

}

if (!(Test-Path "Libraries\include\glm"))
{
    Write-Output "COPYING GLM FILES"
    Copy-Item -Path "../submodules/glm/glm/" -Destination "./Libraries/include/glm/" -Recurse
}

if (!(Test-Path "glad.o"))
{
    Write-Output "COMPILING GLAD"
    g++ -c ..\src\glad\glad.c -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
}

if (!(Test-Path "imgui.o"))
{
    Write-Output "COPYING IMGUI FILES"
    if (Test-Path "..\src\ImGui\")
    {
        Remove-Item "..\src\ImGui\" -Force -Recurse
        mkdir ..\src\ImGui\
    } else {
        mkdir ..\src\ImGui\
    }
    Copy-Item ..\submodules\imgui\backends\imgui_impl_opengl3.h ..\src\ImGui
    Copy-Item ..\submodules\imgui\backends\imgui_impl_opengl3.cpp ..\src\ImGui
    Copy-Item ..\submodules\imgui\backends\imgui_impl_opengl3_loader.h ..\src\ImGui
    Copy-Item ..\submodules\imgui\backends\imgui_impl_glfw.h ..\src\ImGui
    Copy-Item ..\submodules\imgui\backends\imgui_impl_glfw.cpp ..\src\ImGui
    Copy-Item ..\submodules\imgui\*.cpp ..\src\ImGui
    Copy-Item ..\submodules\imgui\*.h ..\src\ImGui
    Write-Output "COMPILING IMGUI"
    g++ -c ..\src\ImGui\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
}


Write-Output "STARTING ENGINE COMPILATION"

g++ -c ..\src\TGEP\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Layers\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Windows\OpenGL\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\RenderApi\OpenGL\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Shader\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/
g++ -c ..\src\TGEP\Renderer\*.cpp -I../src/ -I../src/ImGui/ -I../src/TGEP/ -I./Libraries/include/ -I../src/glad/


ar rcs libTGEP.a *.o

Remove-Item Application.o
Remove-Item Layer.o 
Remove-Item LayerStack.o
Remove-Item ImGuiLayer.o
Remove-Item Input.o
Remove-Item OpenGLWindow.o
Remove-Item OpenGLContext.o
Remove-Item Window.o
Remove-Item OpenGLShader.o
 
Write-Output "ENGINE COMPILATION DONE!"

Write-Output "STARTING COMPILATION OF TEST PROJECT"

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./Libraries/lib/ -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -I./Libraries/include/ -I../src/glad/ -static-libgcc -static-libstdc++

Write-Output "COMPILATION DONE!"


.\sandbox.exe



