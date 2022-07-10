#pragma once

#ifdef TGEP_PLATFORM_WINDOWS

extern TGEP::Application* TGEP::CreateApplication(); 

int main(int argc, char **argv)
{
    auto app = TGEP::CreateApplication();
    app->Run();
    delete app;
}

#endif