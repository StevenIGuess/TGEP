#pragma once 

#include "Events/Event.h"

namespace TGEP
{

    struct WindowProperties
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const std::string& title = "TGEP Window",
            unsigned int width = 1920,
            unsigned int height = 1080)
            : Title(title), Width(width), Height(height)
        {

        }
    };


    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        //Atributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;

        virtual void* GetNativeWindow() const = 0;
    };

}