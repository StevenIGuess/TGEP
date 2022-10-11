#pragma once 

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Layers/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Camera.h"
#include "Layers/OpenGLInfoLayer.h"
#include "DeltaTime.h"

namespace TGEP
{

    struct ApplicationSettings
    {
        bool Vsync = true;
    };

    class Application
    {
    public:
        Application(ApplicationSettings settings);
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }

        void Close();

        inline static Application& Get() { return *s_Instance; }

    private:
        ApplicationSettings m_Settings;
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizedEvent& e);
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;
        LayerStack m_LayerStack;
        static Application* s_Instance;
    };

    //Defined on client side
    Application* CreateApplication();

}