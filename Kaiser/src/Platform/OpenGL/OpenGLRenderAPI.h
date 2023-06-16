#pragma once

#include "Kaiser/Renderer/RenderAPI.h"

namespace Kaiser
{

	class OpenGLRenderAPI : public RenderAPI
	{
	public:


		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	
		
	};
}

