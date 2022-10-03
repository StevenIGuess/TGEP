#pragma once

#include <string>
#include <unordered_map>

namespace TGEP
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetUniform(const std::string& name, const glm::mat4& value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetUniform(const std::string& name, const int& value) = 0;
        virtual void SetUniform(const std::string& name, const float& value) = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        static Ref<Shader> Create(const std::string& path);
    };

    class ShaderLibary
    {
    public:
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& path);
        Ref<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

        Ref<Shader> Get(const std::string& name);
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}