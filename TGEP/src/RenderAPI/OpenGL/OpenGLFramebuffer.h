#pragma once
#include "Renderer/Framebuffer.h"

namespace TGEP
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSettings settings);
		virtual ~OpenGLFramebuffer();

		void Invalidate(); 

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }

		virtual const FramebufferSettings& GetSettings() const { return m_Settings; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FramebufferSettings m_Settings;
	};
}