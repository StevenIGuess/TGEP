#pragma once 
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace TGEP 
{
    
    class DLLEXP Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &e);
    private:

        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    //Defined on client side
    Application* CreateApplication();

}