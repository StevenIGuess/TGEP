#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "DeltaTime.h"

namespace TGEP 
{
    class DLLEXP Layer
    {
    public:
        Layer(const std::string& name = "Layer"); //remove layer name in release versions to safe processing power
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(DeltaTime deltaTime) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event &event) {};

        inline const std::string &GetName() const { return m_DebugName; } //remove later
    protected:
        std::string m_DebugName; //remove later
    };
}