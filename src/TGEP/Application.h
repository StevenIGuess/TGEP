#pragma once 

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Log.h"
#include "LayerStack.h"
#include "Layers/ImGuiLayer.h"
#include "Shader/OpenGlShader.h"

namespace TGEP 
{
    
    class DLLEXP Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
        std::unique_ptr<OpenGLShader> m_Shader;

    private:
        static Application* s_Instance;
    };

    //Defined on client side
    Application* CreateApplication();

}