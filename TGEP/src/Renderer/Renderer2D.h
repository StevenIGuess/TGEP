#pragma once

#include "Camera.h"
#include "Texture.h"
#include "SubTexture2D.h"

namespace TGEP
{
	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4 tint, const Ref<Texture2D>&texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4 tint, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4 tint, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);

		static void DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4& color);
		static void DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4& color);
		static void DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);
		static void DrawQuadR(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4 tint, const Ref<SubTexture2D>& texture, float textureScale = 1.0f);

		struct Satistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static Satistics GetStats();
	private:
		static void StartNewBatch();
	};
}