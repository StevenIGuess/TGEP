#pragma once //

#include <string>

namespace TGEP 
{
    class Shader
    {
    public:

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static Shader* Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}