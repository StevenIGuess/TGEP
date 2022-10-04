#include "pch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace TGEP
{

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TexScale;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000; //MaxQuads (etc.) per draw call
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		PROFILE_FUNCTION()

		uint32_t m_SquareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};


		BufferLayout m_QuadLayout = {
			{ ShaderDataType::Float3 },
			{ ShaderDataType::Float4 },
			{ ShaderDataType::Float2 },
			{ ShaderDataType::Float },
			{ ShaderDataType::Float }
		};


		s_Data.QuadVertexArray = TGEP::VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout(m_QuadLayout);
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> QuadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(QuadIndexBuffer);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&textureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (int32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("assets/Shader/TextureShader.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetUniform("u_Textures", samplers, s_Data.MaxTextureSlots);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
	}
	void Renderer2D::Shutdown()
	{
		PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		PROFILE_FUNCTION();
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetUniform("u_ViewProjection", camera.GetVPM());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		PROFILE_FUNCTION();
		
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		PROFILE_FUNCTION();
		const float textureIndex = 0.0f;
		const float textureScale = 1.0f;

		s_Data.QuadVertexBufferPtr->Position = pos;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y, pos.z};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x , pos.y + size.y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture, textureScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale)
	{
		constexpr glm::vec4 tint = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawQuad(pos, size, tint, texture, textureScale);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, tint, texture, textureScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4 tint,const Ref<Texture2D>& texture, float textureScale)
	{
		PROFILE_FUNCTION();

		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*(s_Data.TextureSlots[i].get()) == *(texture.get()))
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = pos;
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { pos.x , pos.y + size.y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TexScale = textureScale;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		DrawQuadR({ pos.x, pos.y, 0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		PROFILE_FUNCTION();
		s_Data.TextureShader->SetUniform("u_Color", color);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetUniform("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, float textureScale)
	{
		DrawQuadR({ pos.x, pos.y, 0.0f }, size, rotation, texture, textureScale);
	}

	void Renderer2D::DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, float textureScale)
	{
		PROFILE_FUNCTION();
		s_Data.TextureShader->SetUniform("u_Color", glm::vec4(1.0f));
		s_Data.TextureShader->SetUniform("u_TextureScale", textureScale);
		texture->Bind();


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetUniform("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale)
	{
		DrawQuadR({ pos.x, pos.y, 0.0f }, size, rotation, tint, texture, textureScale);
	}

	void Renderer2D::DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale)
	{
		PROFILE_FUNCTION();
		s_Data.TextureShader->SetUniform("u_Color", tint);
		s_Data.TextureShader->SetUniform("u_TextureScale", textureScale);
		texture->Bind();


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetUniform("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
}
