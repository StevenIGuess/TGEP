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

        static void Push(const Ref<VertexArray> &va, const Ref<Shader> &shader, const glm::mat4 &transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 PVM;
        };

        static SceneData* m_SceneData;
    };  
}