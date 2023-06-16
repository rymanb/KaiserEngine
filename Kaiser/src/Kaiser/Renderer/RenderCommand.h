#pragma once

#include "RenderAPI.h"

namespace Kaiser
{
	class RenderCommand
	{
	public:
		inline void static DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			sRenderAPI->DrawIndexed(vertexArray);
		}

		inline void static SetClearColor(const glm::vec4& color)
		{
			sRenderAPI->SetClearColor(color);
		}
		
		inline void static Clear()
		{
			sRenderAPI->Clear();
		}
		
	private:
		static RenderAPI* sRenderAPI;
	};
}