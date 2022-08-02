#pragma once 

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Layers/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "TGEP/Renderer/Buffer.h"
#include "Renderer/Camera.h"
#include "Layers/OpenGLInfoLayer.h"
#include "Layers/TestLayer.h"

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
        TestLayer* m_TestLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

        std::shared_ptr<Shader> m_SquareShader;
        std::shared_ptr<VertexArray> m_SquareVertexArray;
        std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
        std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;

        OrthoCamera m_Camera;

    private:
        static Application* s_Instance;
    };

    //Defined on client side
    Application* CreateApplication();

}