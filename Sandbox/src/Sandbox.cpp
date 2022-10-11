#include <TGEP.h>
#include "EntryPoint.h"
#include <Profiling.h>
#include "imgui/imgui.h"
#include "Sandbox2D.h"


class Sandbox : public TGEP::Application
{
public:

    Sandbox(TGEP::ApplicationSettings settings)
        : Application(settings)
    {
        PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {

    }

};


TGEP::Application* TGEP::CreateApplication()
{
    TGEP::ApplicationSettings settings;
    settings.Vsync = true;
    TGEP::Application* sandbox = new Sandbox(settings);
    return sandbox;
}
