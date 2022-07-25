@echo off

gcc --version
if errorlevel 1 (
    cls
    echo Gcc or Cmake is not installed.
    goto :choice
) 
cmake --version
if errorlevel 1 (
    cls
    echo Gcc or Cmake is not installed.
    goto :choice
)  

:installer
Powershell.exe -NoExit -Command "& {Start-Process Powershell.exe -ArgumentList '-ExecutionPolicy Bypass -File %~dp0installer.ps1' -Verb RunAs}"
goto :installercmake

:endsetup
echo Setup cancelled
exit

:choice
set /P c=Do you want to install MinGW-w64 and Cmake? (y/n)
if /I "%c%" EQU "Y" goto :installer
if /I "%c%" EQU "N" goto :endsetup
goto :choice

