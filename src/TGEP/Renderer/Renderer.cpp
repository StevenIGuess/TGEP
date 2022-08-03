#include "pch.h"
#include "Renderer.h"

namespace TGEP 
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthoCamera &camera)
    {
        m_SceneData->PVM = camera.GetPVM();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Push(const std::shared_ptr<VertexArray> &va, const std::shared_ptr<Shader> &shader, const glm::mat4 &transform)
    {
        shader->Bind();
        shader->UploadUniform("u_ViewProjection", m_SceneData->PVM);
        shader->UploadUniform("u_Transform", transform);
        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}