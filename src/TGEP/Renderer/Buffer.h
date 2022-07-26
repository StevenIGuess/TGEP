#pragma once

namespace TGEP 
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {};
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static VertexBuffer* Create(float* verticies, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {};
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetIndexCount() const = 0;

        static IndexBuffer* Create(uint32_t* indicies, uint32_t count);
    };
}