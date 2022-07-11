#include "Application.h"

#include "Log.h"

namespace TGEP {
    
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);

        LOG_CORE_WARN(e);

        while (true);
    }

}