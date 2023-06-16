#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Kaiser
{

	
	class Renderer
	{
	public:

		static void BeginScene(Camera& camera);
		static void EndScene();
		
		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RenderAPI::API API() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		
		static SceneData* mSceneData;
	};
}
