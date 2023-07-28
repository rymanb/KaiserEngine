#pragma once

#include "RenderAPI.h"

namespace Kaiser
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			sRenderAPI->Init();
		}
		inline void static DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			sRenderAPI->DrawIndexed(vertexArray);
		}

		inline void static DrawIndexed(uint32_t count, bool depthTest)
		{
			sRenderAPI->DrawIndexed(count,  depthTest);
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
		static Ref<RenderAPI> sRenderAPI;
	};
}