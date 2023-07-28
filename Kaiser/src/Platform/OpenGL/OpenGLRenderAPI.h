#pragma once

#include "Kaiser/Renderer/RenderAPI.h"

namespace Kaiser
{

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawIndexed(uint32_t count, bool depthTest) override;
		
	};
}

