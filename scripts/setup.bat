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

gc --version
if errorlevel 1 (
    cls
    echo Gcc is not installed.
    goto :choice
) else (
    exit
)


:installer
echo Installing MinGW-w64 from https://github.com/niXman/mingw-builds-binaries/releases/download/12.1.0-rt_v10-rev3/x86_64-12.1.0-release-win32-seh-rt_v10-rev3.7z.
powershell -File installer.ps1 
exit

:endsetup
echo Setup cancelled
exit

:choice
set /P c=Do you want to install MinGW-w64 and gcc? (y/n)
if /I "%c%" EQU "Y" goto :installer
if /I "%c%" EQU "N" goto :endsetup
goto :choice
