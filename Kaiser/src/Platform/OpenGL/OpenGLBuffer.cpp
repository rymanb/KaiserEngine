#include "stdafx.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include "Kaiser/Renderer/Renderer.h"

Kaiser::OpenGLVertexBuffer::OpenGLVertexBuffer()
{
	Renderer::Submit([this]() {
		glCreateBuffers(1, &mRendererID);
		});
}

Kaiser::OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size) : mSize(size)
{
	mData = Buffer::Copy(vertices, size);
	
	Renderer::Submit([=] {
		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, mData.Data, GL_STATIC_DRAW);
		});
		
}

inline Kaiser::OpenGLVertexBuffer::~OpenGLVertexBuffer() 
{

		glDeleteBuffers(1, &mRendererID);
		mData.Free();
		
}

void Kaiser::OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	Renderer::Submit([=]() {
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		});
}

void Kaiser::OpenGLVertexBuffer::Bind() const
{
	Renderer::Submit([&] {
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(3 * sizeof(float)));
		});
}

void Kaiser::OpenGLVertexBuffer::Unbind() const
{
	Renderer::Submit([&] {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
}

Kaiser::OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int size) : mRendererID(0), mCount(size)
{
	Renderer::Submit([=] {
		glGenBuffers(1, &mRendererID);
		});
}

Kaiser::OpenGLIndexBuffer::OpenGLIndexBuffer(void* indices, uint32_t count) : mCount(count)
{
	mData = Buffer::Copy(indices, count);
	Renderer::Submit([=] {
		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, mData.Data, GL_STATIC_DRAW);
		});
		
}

inline Kaiser::OpenGLIndexBuffer::~OpenGLIndexBuffer() 
{

		glDeleteBuffers(1, &mRendererID);
		mData.Free();
		
}

void Kaiser::OpenGLIndexBuffer::SetData(void* indices, uint32_t count)
{
	Renderer::Submit([=] {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
		});
}

void Kaiser::OpenGLIndexBuffer::Bind() const
{
	Renderer::Submit([&] {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		});
}

void Kaiser::OpenGLIndexBuffer::Unbind() const
{
	Renderer::Submit([&] {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		});
}
