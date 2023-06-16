#include "stdafx.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Kaiser/Trace.h"

Kaiser::VertexBuffer* Kaiser::VertexBuffer::Create(float* vertices, size_t size)
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}

Kaiser::IndexBuffer* Kaiser::IndexBuffer::Create(uint32_t* indices, size_t count)
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, count);
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}
