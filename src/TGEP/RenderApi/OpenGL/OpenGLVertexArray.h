#pragma once

#include "Renderer/VertexArray.h"

namespace TGEP {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        
        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void AddVertexBuffer (const Ref<VertexBuffer> &vertex) override;
        virtual void SetIndexBuffer (const Ref<IndexBuffer> &index) override;

        virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const { return m_VertexBuffers; }
        virtual const Ref<IndexBuffer> &GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
        uint32_t m_RendererID;
    };
}