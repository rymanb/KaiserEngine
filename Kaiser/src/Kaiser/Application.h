#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "Kaiser/LayerStack.h"

namespace Kaiser
{
	class KAISER_API Application
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
		bool running = true;
		
		LayerStack layers;
		
	private:
		static Application* instance;
	};



	// client defined function
	Application* CreateApplication();
}

