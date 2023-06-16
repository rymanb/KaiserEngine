#include "stdafx.h"
#include "Application.h"

#include "Kaiser/Trace.h"

#include "Input.h"

#include "Kaiser/Renderer/Renderer.h"

#include "Scene.h"



#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Kaiser
{
	Application* Application::mInstance = nullptr;
}



Kaiser::Application::Application()
{
	KS_CORE_ASSERT(!mInstance, "Application already exists!");
	mInstance = this;
	
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(BIND_EVENT(OnEvent));

	mGuiLayer = new ImGuiLayer();
	PushOverlay(mGuiLayer);


}

Kaiser::Application::~Application()
{
}

void Kaiser::Application::Run()
{
	Engine::Instance().Init();

	
	while (mRunning)
	{		
		for (Layer* layer : mLayers)
		{
			layer->OnUpdate();
			auto& scene = layer->GetActiveScene();
			if (scene != nullptr)
			{
				scene->Update();
			}
		}

		mGuiLayer->Begin();
		for (Layer* layer : mLayers)
			layer->OnImGuiRender();
		mGuiLayer->End();

		
		mWindow->OnUpdate();
		Engine::Instance().Update(0);


	}
	
	Engine::Instance().Shutdown();
}

void Kaiser::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

	//KS_CORE_TRACE("{0}", e);
	
	for (auto it = mLayers.end(); it != mLayers.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}

}

void Kaiser::Application::PushLayer(Layer* layer)
{
	mLayers.PushLayer(layer);
	layer->OnAttach();
}

void Kaiser::Application::PushOverlay(Layer* layer)
{
	mLayers.PushOverlay(layer);
	layer->OnAttach();
}

bool Kaiser::Application::OnWindowClose(WindowCloseEvent& e)
{
	mRunning = false;

	return true;

}
