@echo off
g++ -o main.exe ..\src\main.cpp ..\src\stb_image.cpp ..\src\glad.c -llibassimp -lopengl32 -lglfw3 -lgdi32

