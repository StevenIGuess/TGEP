# TheGameEngineProject
The Official GitHub repo for the "GameEngineProject"

## What and Why?
This is an GameEngine, that was created for the development of small games using Opengl & C++.
Most of the code is based on the Hazel game engine tutorial series and the learnopengl website.
- https://github.com/TheCherno/Hazel
- https://learnopengl.com/ 

## Used libraries
I'm planning on not using too many libraries, but for the sake of simplicity, I'll still be using the following libraries: 
- Spdlog
- Glm
- Glfw 
- Glad v.4.6.0

These Libraries will (hopefully) later be replaced or removed.

//tmp 

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
