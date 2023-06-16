#include "stdafx.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

Kaiser::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

inline Kaiser::OpenGLVertexBuffer::~OpenGLVertexBuffer() 
{
	glDeleteBuffers(1, &mRendererID);
}

void Kaiser::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void Kaiser::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Kaiser::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : mCount(count)
{
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

inline Kaiser::OpenGLIndexBuffer::~OpenGLIndexBuffer() 
{
	glDeleteBuffers(1, &mRendererID);
}

void Kaiser::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void Kaiser::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
