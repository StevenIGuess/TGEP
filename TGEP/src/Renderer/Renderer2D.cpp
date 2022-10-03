#include "pch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace TGEP
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		PROFILE_FUNCTION()
		s_Data = new Renderer2DData();
		s_Data->QuadVertexArray = TGEP::VertexArray::Create();

		float m_SquareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t m_SquareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};


		BufferLayout m_SquareLayout = {
			{ ShaderDataType::Float3 },
			{ ShaderDataType::Float2 }
		};

		Ref<VertexBuffer> SVB;
		SVB.reset(VertexBuffer::Create(m_SquareVertices, sizeof(m_SquareVertices)));
		SVB->SetLayout(m_SquareLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(SVB);

		Ref<IndexBuffer> SIB;
		SIB.reset(IndexBuffer::Create(m_SquareIndices, (sizeof(m_SquareIndices) / sizeof(uint32_t))));
		s_Data->QuadVertexArray->SetIndexBuffer(SIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&textureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/Shader/TextureShader.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetUniform("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
	{
		PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		PROFILE_FUNCTION();
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetUniform("u_ViewProjection", camera.GetVPM());
	}
	void Renderer2D::EndScene()
	{
		PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		PROFILE_FUNCTION();
		s_Data->TextureShader->SetUniform("u_Color", color);
		s_Data->WhiteTexture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * /* rotation */ glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		PROFILE_FUNCTION();
		s_Data->TextureShader->SetUniform("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * /* rotation */ glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
