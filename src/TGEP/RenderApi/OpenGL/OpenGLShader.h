#pragma once //
#include "Renderer/Shader.h"
#include <string>

namespace TGEP 
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

        virtual void Bind() const override;
        virtual void UnBind() const override;
    private:
        uint32_t m_ShaderID;
    };
}