Clear-Host

Write-Output "Setting vc & path vars"
[Environment]::SetEnvironmentVariable("PATH", $Env:PATH + ";C:\cmake-3.23.2-windows-x86_64\bin\")
$vcdir = ((Get-Content "buildconfig.json") | ConvertFrom-Json).Vcvarsall_dir
pushd $vcdir
Add-Content -Path ".\vcvars64.bat" -Value "set > %temp%\vcvars.txt"
.\vcvars64.bat
if (Test-Path "$env:temp\vcvars.txt") {
    $lines = Get-Content "$env:temp\vcvars.txt"
    foreach($line in $lines) {
        $idx = $line.IndexOf('=')
        if($idx -ne -1) {
            [System.Environment]::SetEnvironmentVariable($line.Substring(0, $idx), $line.Substring($idx + 1))
        }
    }
}
popd

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

    cmake -G "Visual Studio 17 2022" -A x64  -S ..\ -B "build64"
    cmake --build build64 --config Release


    Write-Output "COPYING COMPILED FILES"

    Set-Location ../../../

    Copy-Item -Path "./tmplib/glfw/include/GLFW" -Destination "./Libraries/include/GLFW/" -Recurse
    Copy-Item -Path "./tmplib/glfw/build/build64/src/Release/glfw3.lib" -Destination "./Libraries/lib/" -Recurse

    Write-Output "DELETING OLD FILES"
    
    Remove-Item ".\tmplib" -Force -Recurse

}

if (!(Test-Path "Libraries\include\asio\"))
{
    Write-Output "COPYING ASIO FILES"
    Copy-Item -Path "../submodules/asio/asio/include/*" -Destination "./Libraries/include/" -Recurse
}

if (!(Test-Path "Libraries\include\glm"))
{
    Write-Output "COPYING GLM FILES"
    Copy-Item -Path "../submodules/glm/glm/" -Destination "./Libraries/include/glm/" -Recurse
}

if (!(Test-Path "glad.obj"))
{
    Write-Output "COMPILING GLAD.obj"
    cl /Fo /EHsc /c ../src/glad/glad.c /I..\src\glad\ 
}

if (!(Test-Path "stb_image.obj"))
{
    Write-Output "COMPILING STB_IMAGE"
    cl /Fo /EHsc /c ..\src\stb_image\stb_image.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
}

if (!(Test-Path "imgui.obj"))
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
    cl /Fo /EHsc /c ..\src\ImGui\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ / /I../src/glad/  
}

if (!(Test-Path "implot.obj"))
{
    Write-Output "COPYING IMPLOT FILES"
    if (Test-Path "..\src\ImPlot\")
    {
        Remove-Item "..\src\ImPlot\" -Force -Recurse
        mkdir ..\src\ImPlot\
    } else {
        mkdir ..\src\ImPlot\
    }
    Copy-Item ..\submodules\implot\*.cpp ..\src\ImPlot
    Copy-Item ..\submodules\implot\*.h ..\src\ImPlot
    Write-Output "COMPILING IMPLOT"
    cl /Fo /EHsc /c ..\src\ImPlot\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
}

Write-Output "STARTING ENGINE COMPILATION"

 cl /Fo /EHsc /c  ..\src\TGEP\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
 cl /Fo /EHsc /c  ..\src\TGEP\Layers\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
 cl /Fo /EHsc /c  ..\src\TGEP\Windows\OpenGL\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
 cl /Fo /EHsc /c  ..\src\TGEP\Renderer\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
 cl /Fo /EHsc /c  ..\src\TGEP\RenderAPI\OpenGL\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  
 cl /Fo /EHsc /c  ..\src\TGEP\Networking\*.cpp /I../src/ /I../src/ImGui/ /I../src/TGEP/ /I./Libraries/include/ /I../src/glad/  

 lib *.obj   /OUT:TGEP.lib

Remove-Item Application.obj
Remove-Item Layer.obj 
Remove-Item LayerStack.obj
Remove-Item ImGuiLayer.obj
Remove-Item Input.obj
Remove-Item OpenGLWindow.obj
Remove-Item OpenGLContext.obj
Remove-Item Window.obj
Remove-Item OpenGLShader.obj
Remove-Item Renderer.obj
Remove-Item RendererAPI.obj
Remove-Item Shader.obj
Remove-Item VertexArray.obj
Remove-Item OpenGLBuffer.obj
Remove-Item OpenGLRendererAPI.obj
Remove-Item RenderCommand.obj
Remove-Item Camera.obj

Write-Output "ENGINE COMPILATION DONE!"

Write-Output "STARTING COMPILATION OF TEST PROJECT"

cl /EHsc ..\src\Sandbox\Server.cpp .\Libraries\lib\glfw3.lib .\TGEP.lib /I../src/ /I./Libraries/include/  
cl /EHsc ..\src\Sandbox\sandbox.cpp .\Libraries\lib\glfw3.lib .\TGEP.lib /I../src/ /I./Libraries/include/ /I../src/glad/  

Write-Output "COMPILATION DONE!"

Write-Output "COPYING ASSETS"
if (!(Test-Path "Sandbox/"))
{
    mkdir Sandbox/
}else 
{
    Remove-Item Sandbox/ -Force -Recurse
    mkdir Sandbox/
}
Copy-Item .\sandbox.exe .\Sandbox\
Copy-Item .\server.exe .\Sandbox\
Remove-Item .\sandbox.exe
Remove-Item .\server.exe
Copy-Item ..\src\Sandbox\assets\ .\Sandbox\ -Recurse

Set-Location .\Sandbox\
.\sandbox.exe
Set-Location ..\