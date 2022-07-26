# TheGameEngineProject
The Official GitHub repo for the "GameEngineProject"

## What and Why?
This is an GameEngine, that was created for the development of small games using Opengl & C++.
Most of the code is based on the Hazel game engine tutorial series and the learnopengl website.
- https://github.com/TheCherno/Hazel
- https://learnopengl.com/ 

## Getting started
Clone the repo using:
```
git clone --recurse-submodules https://github.com/StevenIGuess/TGEP.git
```
Now you can run the build file using an _admin_ powershell.
```
cd TGEP\build\
.\build.ps1
```
This file checks for gcc and cmake, installs them if needed and compiles the whole project including depenencies.
If TGEP doesn't compile try clearing the build folder using:
```
.\clear_build_folder.bat && .\clear_libraries.bat
```
If it still doens't work try deleting the folders `C:mingw64` and `C:cmake-3.23.2-windows-x86_64` and rebuilding the project.
If you still encounter issues please open an Issue.

## Used libraries
I'm planning on not using too many libraries, but for the sake of simplicity, I'll still be using the following libraries (all used libraries are added as submodules and dont have to be manualy installed): 
- Glm
- Glfw 
- Glad v.4.6.0

## Using TGEP
After building the system and making sure the `Sandboc.exe` project works fine, you can copy the files `TGEP\src\TGEP.h` and `TGEP\build\libTGEP.a` into your include and lib folders.
