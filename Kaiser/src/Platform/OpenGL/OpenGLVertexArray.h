#pragma once

#include "Kaiser/Renderer/VertexArray.h"

namespace Kaiser
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vert) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override { return mVertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffer;
		uint32_t mId;
		
	};

}

