#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "Kaiser/LayerStack.h"

#include "Kaiser/ImGui/ImGuiLayer.h"

#include "Kaiser/Renderer/Shader.h"

#include "Kaiser/Renderer/Buffer.h"
#include "Kaiser/Renderer/VertexArray.h"

#include "Engine.h"

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

		inline Window& GetWindow() { return *mWindow; }

		inline static Application& Get() { return *mInstance; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		
		std::unique_ptr<Window> mWindow;
		ImGuiLayer* mGuiLayer;
		bool mRunning = true;
		
		LayerStack mLayers;


	private:
		static Application* mInstance;
	};



	// client defined function
	Application* CreateApplication();
}

