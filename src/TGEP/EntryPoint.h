#pragma once

extern TGEP::Application* TGEP::CreateApplication(); 

int main(int argc, char **argv)
{
    printf("\033[0;36m%s\033[0;30m", "TGEP STARTED\n");

    auto app = TGEP::CreateApplication();
    app->Run();
    delete app;
}
