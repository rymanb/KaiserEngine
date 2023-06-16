#include "stdafx.h"
#include "Renderer.h"

namespace Kaiser
{
	Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

	
	void Renderer::BeginScene(Camera& camera)
	{
		mSceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", mSceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}