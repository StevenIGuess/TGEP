#pragma once 
#include "pch.h"
#include "Core.h"

namespace TGEP
{
    class DLLEXP Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();

    private:
        static Input* s_Instance;
    };

}