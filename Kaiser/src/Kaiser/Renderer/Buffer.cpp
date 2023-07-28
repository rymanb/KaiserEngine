#include "stdafx.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Kaiser/Core/Trace.h"

Kaiser::VertexBuffer* Kaiser::VertexBuffer::Create(void* vertices, size_t size)
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}

Kaiser::VertexBuffer* Kaiser::VertexBuffer::Create()
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return new OpenGLVertexBuffer();
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}



Kaiser::Ref<Kaiser::IndexBuffer> Kaiser::IndexBuffer::Create(void* indices, size_t count)
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}

Kaiser::Ref<Kaiser::IndexBuffer> Kaiser::IndexBuffer::Create(unsigned int size)
{
	switch (Renderer::API())
	{
	case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(size);
	}

	KS_CORE_ASSERT(false, "Unknown API!");
	return nullptr;
}
