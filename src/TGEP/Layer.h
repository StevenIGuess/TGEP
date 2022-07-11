#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace TGEP 
{
    class DLLEXP Layer
    {
    public:
        Layer(const std::string& name = "Layer"); //remove layer name in release versions to safe processing power
        ~Layer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event &event);

        inline const std::string &GetName() const { return m_DebugName; } //remove later
    protected:
        std::string m_DebugName; //remove later
    };
}