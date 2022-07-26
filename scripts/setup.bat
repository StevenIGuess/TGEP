@echo off
cls
ECHO This file automatically installs mingw64 and cmake.

:choice
set /P c=Do you wish to continue? (y/n)
if /I "%c%" EQU "Y" goto :install
if /I "%c%" EQU "N" goto :end
goto :choice

:install
Powershell -NoExit -Command "& {Start-Process Powershell.exe -ArgumentList '-ExecutionPolicy Bypass -File %~dp0installer.ps1' -Verb RunAs}"

:end
exit


