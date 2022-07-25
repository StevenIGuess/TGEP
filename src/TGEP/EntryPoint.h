#pragma once

extern TGEP::Application* TGEP::CreateApplication(); 

int main(int argc, char **argv)
{
    printf("%s", "TGEP STARTED");

    auto app = TGEP::CreateApplication();
    app->Run();
    delete app;
}
