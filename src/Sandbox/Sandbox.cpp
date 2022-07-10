#include <TGEP.h>
#define TGEP_PLATFORM_WINDOWS

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