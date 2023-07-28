#include "stdafx.h"
//#include "RenderPass.h"
//
//#include "Renderer.h"
//
//#include "Platform/OpenGL/OpenGLRenderPass.h"
//
//namespace Kaiser {
//
//	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
//	{
//		switch (RenderAPI::API())
//		{
//		case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
//		case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLRenderPass>(spec);
//		}
//
//		KS_CORE_ASSERT(false, "Unknown RendererAPI!");
//		return nullptr;
//	}
//
//}