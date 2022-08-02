#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace TGEP 
{

    class Renderer
    {
    public:
        static void BeginScene(OrthoCamera &camera);
        static void EndScene();

        static void Push(const std::shared_ptr<VertexArray> &va, const std::shared_ptr<Shader> &shader);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 PVM;
        };

        static SceneData* m_SceneData;
    };  
}