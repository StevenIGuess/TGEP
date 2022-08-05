#include "pch.h"
#include "Renderer.h"

#include "RenderAPI/OpenGL/OpenGLShader.h"

namespace TGEP 
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(OrthoCamera &camera)
    {
        m_SceneData->PVM = camera.GetPVM();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Push(const Ref<VertexArray> &va, const Ref<Shader> &shader, const glm::mat4 &transform)
    {
        GLShaderCast(shader)->Bind();
        GLShaderCast(shader)->UploadUniform("u_ViewProjection", m_SceneData->PVM);
        GLShaderCast(shader)->UploadUniform("u_Transform", transform);
        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}