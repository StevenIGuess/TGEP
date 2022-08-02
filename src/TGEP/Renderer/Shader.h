#pragma once //

#include <string>
#include <glm/glm.hpp>

namespace TGEP 
{
    class Shader
    {
    public:
        virtual ~Shader() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void UploadUniform(const std::string &name, const glm::mat4 &value) = 0;

        static Shader* Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}