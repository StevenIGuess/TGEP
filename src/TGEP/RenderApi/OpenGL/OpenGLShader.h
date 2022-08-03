#pragma once
#include "Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>

namespace TGEP 
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        virtual void UploadUniform(const std::string &name, const glm::mat4 &value) override;
        virtual void UploadUniform(const std::string &name, const glm::vec4 &value) override;
    private:
        uint32_t m_ShaderID;
    };
}