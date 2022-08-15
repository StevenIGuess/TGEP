#pragma once

#include "Buffer.h"
#include <memory>

namespace TGEP
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertex) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& index) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();
    };
}