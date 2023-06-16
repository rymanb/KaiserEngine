#include "stdafx.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Kaiser
{
	static GLenum ShaderDataTypeToOpenGLBaseType(Kaiser::ShaderDataType type)
	{
		switch (type)
		{
		case Kaiser::ShaderDataType::Float:	return GL_FLOAT;
		case Kaiser::ShaderDataType::Vec2:	return GL_FLOAT;
		case Kaiser::ShaderDataType::Vec3:	return GL_FLOAT;
		case Kaiser::ShaderDataType::Vec4:	return GL_FLOAT;
		case Kaiser::ShaderDataType::Mat3:		return GL_FLOAT;
		case Kaiser::ShaderDataType::Mat4:		return GL_FLOAT;
		case Kaiser::ShaderDataType::Int:		return GL_INT;
		case Kaiser::ShaderDataType::Int2:		return GL_INT;
		case Kaiser::ShaderDataType::Int3:		return GL_INT;
		case Kaiser::ShaderDataType::Int4:		return GL_INT;
		case Kaiser::ShaderDataType::Bool:		return GL_BOOL;
		}

		KS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
}

Kaiser::OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &mId);
	glBindVertexArray(mId);
}

inline Kaiser::OpenGLVertexArray::~OpenGLVertexArray() 
{
	glDeleteVertexArrays(1, &mId);
}

void Kaiser::OpenGLVertexArray::Bind() const
{
	glBindVertexArray(mId);
}

void Kaiser::OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void Kaiser::OpenGLVertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vert)
{
	KS_CORE_ASSERT(vert->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
	
	glBindVertexArray(mId);
	vert->Bind();
	
	uint32_t i = 0;
	const auto& layout = vert->GetLayout();
	for (const auto& e : layout)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
			e.GetElementCount(),
			Kaiser::ShaderDataTypeToOpenGLBaseType(e.Type),
			e.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)e.Offset);
		i++;
	}

	mVertexBuffers.push_back(vert);

	
	
}

void Kaiser::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index)
{
	glBindVertexArray(mId);
	index->Bind();
	mIndexBuffer = index;
}
