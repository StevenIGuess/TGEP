#pragma once
#include "TGEP/Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

#define GLShaderCast(...) std::dynamic_pointer_cast<TGEP::OpenGLShader>(__VA_ARGS__)

//TEMPORARY
typedef unsigned int GLenum;

namespace TGEP
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& path);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual const std::string& GetName() const override { return m_Name; }

        virtual void UploadUniform(const std::string& name, const glm::mat4& value);
        virtual void UploadUniform(const std::string& name, const glm::vec4& value);
        virtual void UploadUniform(const std::string& name, const int& value);
    private:
        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        std::string m_Name;

        uint32_t m_RendererID;
    };
}