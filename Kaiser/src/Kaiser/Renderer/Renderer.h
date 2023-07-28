#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

#include "RenderCommandQueue.h"
#include "Mesh.h"



namespace Kaiser
{



	
	class Renderer 
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		// Commands

		
		static void Init();
		static Scope<ShaderManager>& GetShaderManager();
		

		template<typename FuncT>
		static void Submit(FuncT&& func)
		{
			auto renderCmd = [](void* ptr) {
				auto pFunc = (FuncT*)ptr;
				(*pFunc)();

				// NOTE: Instead of destroying we could try and enforce all items to be trivally destructible
				// however some items like uniforms which contain std::strings still exist for now
				// static_assert(std::is_trivially_destructible_v<FuncT>, "FuncT must be trivially destructible");
				pFunc->~FuncT();
			};
			auto storageBuffer = GetRenderCommandQueue().Allocate(renderCmd, sizeof(func));
			new (storageBuffer) FuncT(std::forward<FuncT>(func));
		}

		static void BeginScene(Camera& camera);
		static void EndScene();
		
		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static void WaitAndRender();

		static void DrawIndexed(unsigned int count, bool depthTest = true);

		static void Clear(glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) 
		{ 
			Submit([=] {
				RenderCommand::SetClearColor(color);
				RenderCommand::Clear();
				});
		}

		inline static RenderAPI::API API() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		
		static Ref<Renderer::SceneData> mSceneData;

		static RenderCommandQueue& GetRenderCommandQueue();
	};
}
