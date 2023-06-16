#pragma once

#include "Buffer.h"

namespace Kaiser
{
	class VertexArray : public Buffer
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vert) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}