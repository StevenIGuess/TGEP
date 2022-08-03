#pragma once
#include "TGEP/Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>

#define GLShaderCast(...) std::dynamic_pointer_cast<TGEP::OpenGLShader>(__VA_ARGS__)

namespace TGEP 
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        virtual void UploadUniform(const std::string &name, const glm::mat4 &value);
        virtual void UploadUniform(const std::string &name, const glm::vec4 &value);
    private:
        uint32_t m_ShaderID;
    };
}