#pragma once 
#define TGEP_PLATFORM_WINDOWS
#define TGEP_BUILD_DLL

namespace TGEP 
{
    
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    //Defined on client side
    Application* CreateApplication();

}