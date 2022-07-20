@echo off
cls

if not exist "imgui.o" (

    echo COMPILING IMGUI

    g++ -c ..\vendor\imgui\

    g++ -c ..\vendor\imgui\imgui.cpp
    g++ -c ..\vendor\imgui\imgui_draw.cpp
    g++ -c ..\vendor\imgui\imgui_tables.cpp
    g++ -c ..\vendor\imgui\imgui_widgets.cpp
    g++ -c ..\vendor\imgui\imgui_impl_opengl3.cpp
    g++ -c ..\vendor\imgui\imgui_demo.cpp
    g++ -c ..\vendor\imgui\imgui_impl_glfw.cpp
)

if not exist "glad.o" (

    echo COMPILING GLAD

    g++ -c ..\src\TGEP\glad\glad.c 
)

echo STARTING ENGINE COMPILATION

g++ -c ..\src\TGEP\Application.cpp       
g++ -c ..\src\TGEP\Log.cpp
g++ -c ..\src\TGEP\Layer.cpp 
g++ -c ..\src\TGEP\LayerStack.cpp 
g++ -c ..\src\TGEP\Layers\ImGuiLayer.cpp
g++ -c ..\src\TGEP\Input.cpp
g++ -c ..\src\TGEP\Windows\OpenGL\OpenGLWindow.cpp
g++ -c ..\src\TGEP\RenderApi\OpenGL\OpenGLContext.cpp
g++ -c ..\src\TGEP\Window.cpp

ar rcs libTGEP.a Application.o Log.o Layer.o LayerStack.o glad.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o ImGuiLayer.o Input.o OpenGLWindow.o OpenGLContext.o Window.o

del Application.o
del Log.o
del Layer.o 
del LayerStack.o
del ImGuiLayer.o
del Input.o
del OpenGLWindow.o
del OpenGLContext.o
del Window.o

echo ENGINE COMPILATION DONE!

echo STARTING COMPILATION OF TEST PROJECT

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -static-libgcc -static-libstdc++

echo COMPILATION DONE!



.\sandbox.exe