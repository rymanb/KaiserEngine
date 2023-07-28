#include "stdafx.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Kaiser
{


	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::API())
		{
		case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		KS_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

}