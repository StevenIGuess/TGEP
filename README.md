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
If you have mingw64 and cmake installed you can skip this step, else install them using the setup.bat file
```
cd TGEP\scripts\
.\setup.bat
```
Now you can build the system using the build.bat file
```
cd ..\build\
.\build.bat
```
If TGEP doesn't compile try clearing the build folder using
```
.\clear_build_folder.bat
```

## Used libraries
I'm planning on not using too many libraries, but for the sake of simplicity, I'll still be using the following libraries: 
- Glm
- Glfw 
- Glad v.4.6.0

These Libraries will (hopefully) later be replaced or removed.
