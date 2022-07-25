@echo off
cls
:: BatchGotAdmin
    IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

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

gcc --version
if errorlevel 1 (
    cls
    echo Gcc is not installed.
    goto :choicegcc
) else (
    goto :checkcmake
    exit
)


:installergcc
echo Installing MinGW-w64 from https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z @ C:\mingw64
START /WAIT Powershell.exe -Command "& {Start-Process Powershell.exe -ArgumentList '-ExecutionPolicy Bypass -File %~dp0installergcc.ps1' -Verb RunAs}"
goto :checkcmake

:installercmake
echo Installing Cmake from https://github.com/Kitware/CMake/releases/download/v3.23.2/cmake-3.23.2-windows-x86_64.zip @ C:\cmake-3.23.2-windows-x86_64
START /WAIT Powershell.exe -Command "& {Start-Process Powershell.exe -ArgumentList '-ExecutionPolicy Bypass -File %~dp0installercmake.ps1' -Verb RunAs}"
exit

:endsetup
echo Setup cancelled
exit

:choicegcc
set /P c=Do you want to install MinGW-w64 and gcc? (y/n)
if /I "%c%" EQU "Y" goto :installergcc
if /I "%c%" EQU "N" goto :endsetup
goto :choicegcc

:choicecmake
set /P c=Do you want to install Cmake? (y/n)
if /I "%c%" EQU "Y" goto :installercmake
if /I "%c%" EQU "N" goto :endsetup
goto :choicecmake

:checkcmake
cmake --version
if errorlevel 1 (
    cls
    echo Cmake is not installed.
    goto :choicecmake
) else (
    postsetup.bat
    exit
)

