#include <TGEP.h>

class Sandbox : public TGEP::Application
{
public:

    Sandbox()
    {
        PushOverlay(new TGEP::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

TGEP::Application* TGEP::CreateApplication()
{
    return new Sandbox();
}