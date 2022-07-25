@echo off
cls
set PATH=%PATH%;C:\mingw64\bin\;C:\cmake-3.23.2-windows-x86_64\bin\

if not exist "imgui.o" (

    echo COMPILING IMGUI

    g++ -c ..\src\TGEP\ImGui\imgui.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_draw.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_tables.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_widgets.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_impl_opengl3.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_demo.cpp
    g++ -c ..\src\TGEP\ImGui\imgui_impl_glfw.cpp
)

if not exist "glad.o" (

    echo COMPILING GLAD

    g++ -c ..\src\TGEP\glad\glad.c 
)

echo STARTING ENGINE COMPILATION

g++ -c ..\src\TGEP\Application.cpp       
g++ -c ..\src\TGEP\Log.cpp
g++ -c ..\src\TGEP\Window.cpp  
g++ -c ..\src\TGEP\Layer.cpp 
g++ -c ..\src\TGEP\LayerStack.cpp 
g++ -c ..\src\TGEP\Layers\ImGuiLayer.cpp
g++ -c ..\src\TGEP\Input.cpp

ar rcs libTGEP.a Application.o Log.o Window.o Layer.o LayerStack.o glad.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o ImGuiLayer.o Input.o

del Application.o
del Log.o
del Window.o
del Layer.o 
del LayerStack.o
del ImGuiLayer.o
del Input.o

echo ENGINE COMPILATION DONE!