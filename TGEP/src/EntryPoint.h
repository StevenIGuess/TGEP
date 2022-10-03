#pragma once
#include "Profiling.h"
extern TGEP::Application* TGEP::CreateApplication();

int main(int argc, char** argv)
{

    printf("\033[0;36m%s\033[0m", "TGEP STARTED\n");

    PROFILE_BEGIN("Startup", "TGEP_STARTUP.json");
    auto app = TGEP::CreateApplication();
    PROFILE_END();

    PROFILE_BEGIN("Runtime", "TGEP_RUNTIME.json");
    app->Run();
    PROFILE_END();

    PROFILE_BEGIN("Shutdown", "TGEP_SHUTDOWN.json");
    delete app;
    PROFILE_END();
}
