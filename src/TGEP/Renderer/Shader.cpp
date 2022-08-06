#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "../RenderAPI/OpenGl/OpenGLShader.h"

namespace TGEP
{
    Ref<Shader> Shader::Create(const std::string &path)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(path);
            case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;
            
        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "No Renderer selected"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
            case RendererAPI::API::DirectX:  ASSERT_CORE(false, "DirectX not implemented yet"); return nullptr;
        }

        ASSERT_CORE(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibary::Add(const Ref<Shader>& shader)
    {
        std::string name = shader->GetName();
        ASSERT_CORE(m_Shaders.find(name) == m_Shaders.end(), "ERROR::DUPLICATE_SHADER_DEFINITION");
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibary::Load(const std::string &path)
    {
        Ref<Shader> shader = Shader::Create(path);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibary::Load(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        Ref<Shader> shader = Shader::Create(name, vertexSrc, fragmentSrc);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibary::Get(const std::string &name)
    {
        ASSERT_CORE(m_Shaders.find(name) != m_Shaders.end(), "ERROR::SHADER_NOT_FOUND");
        return m_Shaders[name];
    }

}