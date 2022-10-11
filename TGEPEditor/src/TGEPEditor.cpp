#include <TGEP.h>
#include "EntryPoint.h"
#include <Profiling.h>
#include "imgui/imgui.h"
#include "EditorLayer.h"

namespace TGEP
{
    class TGEPEditor : public Application
    {
    public:

        TGEPEditor(ApplicationSettings settings)
            : Application(settings)
        {
            PushLayer(new EditorLayer());
        }

        ~TGEPEditor()
        {

        }

    };


    TGEP::Application* CreateApplication()
    {
        ApplicationSettings settings;
        settings.Vsync = false;

        TGEP::Application* editor = new TGEPEditor(settings);
        return editor;
    }
}
