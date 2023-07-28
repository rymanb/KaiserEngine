#include "stdafx.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Kaiser
{
	Ref<Renderer::SceneData> Renderer::mSceneData = CreateRef<Renderer::SceneData>();

	struct RendererData
	{
		RenderCommandQueue m_CommandQueue;
		Scope<ShaderManager> m_ShaderLibrary;

	};

	static RendererData s_Data;
	
	void Renderer::Init()
	{
		RenderCommand::Init();
		s_Data.m_ShaderLibrary = CreateScope<ShaderManager>();
		
	}

	void Renderer::BeginScene(Camera& camera)
	{
		Renderer::Submit([=] {
			mSceneData->ViewProjectionMatrix = camera.GetViewProjection();
			});
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		//Renderer::Submit([shader, vertexArray, transform] {
			shader->Bind();
			shader->SetMat4("u_ViewProjection", mSceneData->ViewProjectionMatrix);
			shader->SetMat4("u_Transform", transform);
			vertexArray->Bind();
			Renderer::Submit([=] {
				RenderCommand::DrawIndexed(vertexArray);
				});
			//});
	}

	void Renderer::DrawIndexed(unsigned int count, bool depthTest)
	{
		Renderer::Submit([=] {
			RenderCommand::DrawIndexed(count, depthTest);
			});
	}

	void Renderer::WaitAndRender()
	{
		s_Data.m_CommandQueue.Execute();
	}

	Scope<ShaderManager>& Renderer::GetShaderManager()
	{
		// TODO: insert return statement here
		return s_Data.m_ShaderLibrary;
	}

	RenderCommandQueue& Renderer::GetRenderCommandQueue()
	{
		return s_Data.m_CommandQueue;
	}

}