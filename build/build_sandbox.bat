[Environment]::SetEnvironmentVariable('PATH', ${env:path} + ';C:\mingw64\bin\', 'Machine')

g++ -o sandbox.exe ..\src\Sandbox\sandbox.cpp -L./ -lTGEP -lglfw3 -lgdi32 -lopengl32 -I../src/ -static-libgcc -static-libstdc++