#include "pch.h"
#include "Renderer.h"
#include "Renderer2D.h"

#include "RenderAPI/OpenGL/OpenGLShader.h"

#define GLShaderCast(...) std::dynamic_pointer_cast<TGEP::OpenGLShader>(__VA_ARGS__)

namespace TGEP
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        PROFILE_FUNCTION()
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthoCamera& camera)
    {
        m_SceneData->PVM = camera.GetVPM();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Push(const Ref<VertexArray>& va, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        GLShaderCast(shader)->Bind();
        GLShaderCast(shader)->UploadUniform("u_ViewProjection", m_SceneData->PVM);
        GLShaderCast(shader)->UploadUniform("u_Transform", transform);
        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}