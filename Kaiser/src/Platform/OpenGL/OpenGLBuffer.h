#pragma once

#include "Kaiser/Renderer/Buffer.h"
#include "Kaiser/Core/Buffer.h"

namespace Kaiser
{
	
	
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		OpenGLVertexBuffer(void* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void SetData(const void* data, uint32_t size) override;
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return mLayout; }
		virtual void SetLayout(const BufferLayout& layout) override { mLayout = layout; }

		

	private:
		uint32_t mRendererID;
		BufferLayout mLayout;

		uint32_t mSize;
		Buffer mData;
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int size);
		OpenGLIndexBuffer(void* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void SetData(void* indices, uint32_t count) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override 
		{ 
			return mCount / sizeof(uint32_t);
		}
	private:
		uint32_t mRendererID;
		uint32_t mCount;
		Buffer mData;
	};
}
