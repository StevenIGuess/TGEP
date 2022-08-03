#include "pch.h"
#include "OpenGLVertexArray.h"


namespace TGEP {

    static GLenum TGEPTypeToGLType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Bool:      return GL_BOOL;
        }
        ASSERT_CORE(false, "UNKNOWN_SHADER_DATA_TYPE@Application.cpp");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertex)
    {
        ASSERT_CORE(vertex->GetLayout().GetElements().size(), "VERTEX_BUFFER_LAYOUT_MISSING");

        glBindVertexArray(m_RendererID);
        vertex->Bind();

        uint32_t i = 0;
        const auto &layout = vertex->GetLayout();
        for (const BufferElement element : layout.GetElements())
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.GetComponentCount(), TGEPTypeToGLType(element.Type),
                                     element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
            i++;
        }
        m_VertexBuffers.push_back(vertex);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &index)
    {
        glBindVertexArray(m_RendererID);
        index->Bind();
        m_IndexBuffer = index;
    }

}