@echo off

set filesToBuild=..\src\main.c ..\src\shader.c ..\src\textureLoader.c ..\src\eventHandler.c ..\src\stb_image.c ..\src\glad.c

set addFlags=-llibassimp -lopengl32 -lglfw3 -lgdi32

gcc -o main.exe %filesToBuild% %addFlags%

