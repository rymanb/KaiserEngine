#include "stdafx.h"
#include "Application.h"

#include "Kaiser/Trace.h"

#include <glad/glad.h>

#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Kaiser
{
	Application* Application::instance = nullptr;
}

Kaiser::Application::Application()
{
	KS_CORE_ASSERT(!instance, "Application already exists!");
	instance = this;
	
	window = std::unique_ptr<Window>(Window::Create());
	window->SetEventCallback(BIND_EVENT(OnEvent));
}

Kaiser::Application::~Application()
{
}

void Kaiser::Application::Run()
{


	while (running)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (Layer* layer : layers)
			layer->OnUpdate();
		
		window->OnUpdate();
	}
}

void Kaiser::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

	KS_CORE_TRACE("{0}", e);
	
	for (auto it = layers.end(); it != layers.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}

}

void Kaiser::Application::PushLayer(Layer* layer)
{
	layers.PushLayer(layer);
	layer->OnAttach();
}

void Kaiser::Application::PushOverlay(Layer* layer)
{
	layers.PushOverlay(layer);
	layer->OnAttach();
}

bool Kaiser::Application::OnWindowClose(WindowCloseEvent& e)
{
	running = false;

	return true;

}
