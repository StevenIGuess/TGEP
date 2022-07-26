#pragma once

namespace TGEP 
{
    enum class RendererAPI
    {
        None = 0, OpenGL = 1, DirectX = 2
    };

    class Renderer
    {
    public:
        inline static RendererAPI GetRendererAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };

    
}