#pragma once

extern TGEP::Application* TGEP::CreateApplication(); 

int main(int argc, char **argv)
{
    TGEP::Log::Init();

    LOG_CORE_INFO("TGEP STARTED");

    auto app = TGEP::CreateApplication();
    app->Run();
    delete app;
}
