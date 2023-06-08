#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "Kaiser/LayerStack.h"

#include "Kaiser/ImGui/ImGuiLayer.h"

#include "Kaiser/Renderer/Shader.h"

namespace Kaiser
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *window; }

		inline static Application& Get() { return *instance; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		
		std::unique_ptr<Window> window;
		ImGuiLayer* guiLayer;
		bool running = true;
		
		LayerStack layers;

		unsigned int vertexArray, vertexBuffer, indexBuffer;
		std::unique_ptr<Shader> shader;
		
	private:
		static Application* instance;
	};



	// client defined function
	Application* CreateApplication();
}

