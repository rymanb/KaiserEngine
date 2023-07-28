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

		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vert) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& index) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return mVertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffer; }

	private:
		std::vector<Ref<VertexBuffer>> mVertexBuffers;
		Ref<IndexBuffer> mIndexBuffer;
		uint32_t mId;
		
	};

}

