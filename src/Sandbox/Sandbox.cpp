#include <TGEP.h>

class Sandbox : public TGEP::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

TGEP::Application* TGEP::CreateApplication()
{
    return new Sandbox();
}