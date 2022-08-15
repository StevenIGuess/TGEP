#pragma once

#include <string>
#include "../Core.h"

namespace TGEP
{
    class Texture2D
    {
    public:
        virtual ~Texture2D() = default;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        static Ref<Texture2D> Create(const std::string& path);
    };

}