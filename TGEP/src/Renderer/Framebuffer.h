#pragma once

#include "Core.h"

namespace TGEP
{
	struct FramebufferSettings
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual const FramebufferSettings& GetSettings() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSettings& settings);

		virtual ~Framebuffer() = default;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
	};
}