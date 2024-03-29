#pragma once
#include "Renderer/Shader.h"
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

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

        virtual void SetUniform(const std::string& name, const glm::mat4& value) override;
        virtual void SetUniform(const std::string& name, const glm::vec4& value) override;
        virtual void SetUniform(const std::string& name, const int value) override;
        virtual void SetUniform(const std::string& name, const int* values, uint32_t count) override;
        virtual void SetUniform(const std::string& name, const float value) override;

        virtual const std::string& GetName() const override { return m_Name; }

        virtual void UploadUniform(const std::string& name, const glm::mat4& value);
        virtual void UploadUniform(const std::string& name, const glm::vec4& value);
        virtual void UploadUniform(const std::string& name, const int value);
        virtual void UploadUniform(const std::string& name, const int* values, uint32_t count);
        virtual void UploadUniform(const std::string& name, const float value);
    private:
        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        std::string m_Name;

        uint32_t m_RendererID;
    };
}