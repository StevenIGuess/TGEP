#pragma once
#include <cstdint>
#include <vector>
#include "../Core.h"

namespace TGEP 
{
    #define TGEPFloat ShaderDataType::Float 
    #define TGEPFloat2 ShaderDataType::Float2 
    #define TGEPFloat3 ShaderDataType::Float3 
    #define TGEPFloat4 ShaderDataType::Float4 
    #define TGEPMat3 ShaderDataType::Mat3 
    #define TGEPMat4 ShaderDataType::Mat4 
    #define TGEPBool ShaderDataType::Bool 

    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }

        ASSERT_CORE(false, "UNKNOWN_SHADER_DATA_TYPE@Buffer.h");
        return 0;
    }

    struct BufferElement
    {
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, bool normalized = false) : Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

        uint32_t GetComponentCount() const
        { 
            switch (Type)
            {
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Mat3:      return 3 * 3;
                case ShaderDataType::Mat4:      return 4 * 4;
                case ShaderDataType::Bool:      return 1;
            }

            ASSERT_CORE(false, "UNKNOWN_SHADER_DATA_TYPE@Buffer.h");
            return 0;
        }
    };
    

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement> &element) : m_Elements(element) 
        {
            CalcOffsetAndStride();
        };
        
        uint32_t GetStride() const { return m_Stride; }
        const std::vector<BufferElement> &GetElements() const { return m_Elements; } 


    private:
        void CalcOffsetAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for(auto &element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {};
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetLayout(const BufferLayout &layout) = 0;
        virtual const BufferLayout &GetLayout() const = 0;

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