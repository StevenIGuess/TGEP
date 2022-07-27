# TGEP - Notes

## Layout:

- Entery point
- Application layer
- Window Layer
    - Input
    - Events
- Renderer 
- Opengl abstraction
- Debug support (Loging, etc.)
- Script language
- Memory system 
- ECS
- File I/O & VFS
- Physics engine 
- (Animation system)
- Build system

## ToDo: 

Create basic build system (DONE)
Add entry point (DONE)
Add logging system (DONE)
Add event system (DONE)
Switch to static library


## ToDo (Later):

    Replace SPDLOG with own logging system
    Add licenses 
    Make games dll files and TGEP an executable that "launches" the dll games.
    Add support for modding in form of extra dlls 

## ToDo (Production): 

Remove layer name in release versions to save processing power

<<<<<<< HEAD
=======
## dependencies (dumpbin /dependents)

File Type: DLL (TGEP.dll)

  Image has the following dependencies:

    libgcc_s_seh-1.dll
    libstdc++-6.dll
    GDI32.dll (resolved by windows)
    KERNEL32.dll (resolved by windows)
    api-ms-win-crt-time-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-string-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-stdio-l1-1-0.dll
    api-ms-win-crt-runtime-l1-1-0.dll 
    api-ms-win-crt-filesystem-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-locale-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-convert-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-private-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-environment-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-math-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-heap-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-utility-l1-1-0.dll (resolved by windows)
    libwinpthread-1.dll
    SHELL32.dll (resolved by windows)
    USER32.dll (resolved by windows)

Remaining (Not resolved by windows):

    libgcc_s_seh-1.dll
    libstdc++-6.dll
    api-ms-win-crt-stdio-l1-1-0.dll
    api-ms-win-crt-runtime-l1-1-0.dll
    libwinpthread-1.dll

File Type: EXECUTABLE IMAGE (sandbox.exe) //not important for TGEP

  Image has the following dependencies:

    KERNEL32.dll (resolved by windows)
    api-ms-win-crt-time-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-string-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-stdio-l1-1-0.dll (resolved by TGEP lib)
    api-ms-win-crt-runtime-l1-1-0.dll (resolved by TGEP lib)
    api-ms-win-crt-filesystem-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-locale-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-convert-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-private-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-environment-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-math-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-heap-l1-1-0.dll (resolved by windows)
    api-ms-win-crt-utility-l1-1-0.dll (resolved by windows)
    libwinpthread-1.dll (resolved by TGEP lib)
    TGEP.dll


BUILDSYSTEM Tested on: Hyper-V/win10/4gb/6cores;Win11(dev machine, clean path)/16gb/6cores;Win10/32gb/6cores;
