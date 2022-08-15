#pragma once

namespace TGEP
{
    class RenderContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}