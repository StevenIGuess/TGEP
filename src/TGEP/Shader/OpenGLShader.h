#pragma once //

#include <string>

namespace TGEP 
{
    class OpenGLShader
    {
    public:

        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

        void Bind() const;
        void UnBind() const;
    private:
        uint32_t m_ShaderID;
    };
}