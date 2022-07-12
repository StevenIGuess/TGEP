@echo off
cls

if not exist "imgui.o" (

    echo COMPILING IMGUI

    g++ -c ..\src\TGEP\ImGui\imgui.cpp ..\src\TGEP\ImGui\imgui_draw.cpp  ..\src\TGEP\ImGui\imgui_tables.cpp  ..\src\TGEP\ImGui\imgui_widgets.cpp ..\src\TGEP\ImGui\ImGuiOpenGlRenderer.cpp ..\src\TGEP\ImGui\imgui_demo.cpp
)

if not exist "glad.o" (

    echo COMPILING GLAD

    g++ -c ..\src\TGEP\glad.c 
)

echo STARTING ENGINE COMPILATION

g++ -c ..\src\TGEP\Application.cpp ..\src\TGEP\Log.cpp ..\src\TGEP\Window.cpp ..\src\TGEP\Layer.cpp ..\src\TGEP\LayerStack.cpp  ..\src\TGEP\Layers\ImGuiLayer.cpp

g++ -shared -o TGEP.dll Application.o Log.o Window.o Layer.o LayerStack.o glad.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o ImGuiOpenGlRenderer.o imgui_demo.o ImGuiLayer.o -lopengl32 -lglfw3 -lgdi32

del Application.o
del Log.o
del Window.o
del Layer.o 
del LayerStack.o
del ImGuiLayer.o

echo ENGINE COMPILATION DONE!

echo STARTING COMPILATION OF TEST PROJECT

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -I ..\src

echo COMPILATION DONE!



.\sandbox.exe