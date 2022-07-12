#pragma once 

#include "pch.h"

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"

//test include 
#include "ImGui/imgui.h"


namespace TGEP 
{

    struct WindowProperties
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const std::string& title = "TGEP Window",
                        unsigned int width  = 1920,
                        unsigned int height = 1080)
            : Title(title), Width(width), Height(height)
        {

        }
    };

    
    class DLLEXP Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProperties& properties);

        ~Window();

        void OnUpdate();

        unsigned int GetWidth() { return m_Data.Width; }
        unsigned int GetHeight() { return m_Data.Height; }

        //Atributes
        void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVsync() const;

        virtual void* GetWindow() const { return m_Window; }

        static Window* Create(const WindowProperties& props = WindowProperties());
    private:
        virtual void Init(const WindowProperties& properties);
        virtual void Shutdown();
    private:

        GLFWwindow* m_Window;
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