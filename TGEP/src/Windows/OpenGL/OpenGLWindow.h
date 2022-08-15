#pragma once 

#include "../../Window.h"
#include "../../RenderApi/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace TGEP
{

    class DLLEXP OpenGLWindow : public Window
    {
    public:

        OpenGLWindow(const WindowProperties& properties);
        virtual ~OpenGLWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        //Atributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVsync() const override;

        void* GetNativeWindow() const { return m_Window; }

        static Window* Create(const WindowProperties& properties = WindowProperties());
    private:
        void Init(const WindowProperties& properties);
        void Shutdown();
    private:
        GLFWwindow* m_Window;
        RenderContext* m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;

    };

}