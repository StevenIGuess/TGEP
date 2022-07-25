@echo off
Powershell -NoExit -Command "& {Start-Process Powershell.exe -ArgumentList '-ExecutionPolicy Bypass -File %~dp0installer.ps1' -Verb RunAs}"