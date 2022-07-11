#include <TGEP.h>

class TestLayer : public TGEP::Layer
{
public:
    TestLayer() : Layer("TestLayer")
    {

    }

    void OnUpdate() override
    {
        LOG_INFO("Layer update");
    }

    void OnEvent(TGEP::Event &e) override
    {
        LOG_INFO("EVENT: {0}", e);
    }
};


class Sandbox : public TGEP::Application
{
public:

    Sandbox()
    {
        PushLayer(new TestLayer());
    }

    ~Sandbox()
    {

    }
};

TGEP::Application* TGEP::CreateApplication()
{
    return new Sandbox();
}