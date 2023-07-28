#include "stdafx.h"
#include "Framebuffer.h"

#include "Kaiser/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"




namespace Kaiser {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		Ref<Framebuffer> result = nullptr;

		switch (Renderer::API())
		{
		case RenderAPI::API::None:		return nullptr;
		case RenderAPI::API::OpenGL:	result = std::make_shared<OpenGLFramebuffer>(spec);
		}
		FramebufferPool::GetGlobal()->Add(result);
		return result;
	}


	Ref<FramebufferPool> FramebufferPool::s_Instance = CreateRef<FramebufferPool>();

	FramebufferPool::FramebufferPool(uint32_t maxFBs /* = 32 */)
	{

	}

	FramebufferPool::~FramebufferPool()
	{

	}

	std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
	{
		// m_Pool.push_back();
		return std::weak_ptr<Framebuffer>();
	}

	void FramebufferPool::Add(std::weak_ptr<Framebuffer> framebuffer)
	{
		m_Pool.push_back(framebuffer);
	}

}