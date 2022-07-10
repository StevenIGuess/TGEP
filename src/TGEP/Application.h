#pragma once 
#include "Core.h"

namespace TGEP 
{
    
    class DLLEXP Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    //Defined on client side
    Application* CreateApplication();

}