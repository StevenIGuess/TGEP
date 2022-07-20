#include "../TGEP.h"
class Testlayer : public TGEP::Layer
{
public:
    Testlayer() : Layer("Example")
    {

    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("test");
        ImGui::Text("Hello, World!");
        ImGui::End();
    }
};

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