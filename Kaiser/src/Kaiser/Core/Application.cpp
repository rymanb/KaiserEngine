#include "stdafx.h"
#include "Application.h"

#include "Kaiser/Core/Trace.h"

#include "Input.h"

#include "Kaiser/Renderer/Renderer.h"

#include "Kaiser/Scene/Scene.h"

#include "Kaiser/Scene/SceneManager.h"
#include "Kaiser/Entity/ComponentFactory.h"

#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "glad/glad.h"

#include <imgui.h>

#include "Kaiser/Renderer/Framebuffer.h"


#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Kaiser
{
	Application* Application::mInstance = nullptr;
}

void Kaiser::Application::InitEngine()
{
	IEngine& engine = Engine::Instance();
	engine.Add<SceneManager>();
	engine.Add<ComponentFactory>();
	
	Engine::Instance().Init();
	
}

std::string Kaiser::Application::OpenFile(const std::string& filter) const
{
	OPENFILENAMEA ofn;       // common dialog box structure
	CHAR szFile[260] = { 0 };       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)mWindow->GetNativeWindow());
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return std::string();
}


Kaiser::Application::Application()
{
	KS_CORE_ASSERT(!mInstance, "Application already exists!");
	mInstance = this;
	
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(BIND_EVENT(OnEvent));

	InitEngine();

	Renderer::Init();

	mGuiLayer = new ImGuiLayer();
	PushOverlay(mGuiLayer);


}

Kaiser::Application::~Application()
{
}

void Kaiser::Application::Run()
{


	
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

		Renderer::Submit([=] {
			RenderImGui();
			});

		Renderer::WaitAndRender();
		
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

bool Kaiser::Application::OnWindowResize(WindowResizeEvent& e)
{
	int width = e.GetWidth(), height = e.GetHeight();
	Renderer::Submit([=] 
		{ 
			glViewport(0, 0, width, height); 
		});
	auto& fbs = FramebufferPool::GetGlobal()->GetAll();
	for (auto& fb : fbs)
	{
		auto sp = fb.lock();
		if (sp)
		{
			sp->Resize(width, height);
		}
	}
	return false;
}

void Kaiser::Application::RenderImGui()
{
	mGuiLayer->Begin();

	ImGui::Begin("Renderer");
	
	auto& caps = RenderAPI::GetCapabilities();
	ImGui::Text("Vendor: %s", caps.Vendor.c_str());
	ImGui::Text("Renderer: %s", caps.Renderer.c_str());
	ImGui::Text("Version: %s", caps.Version.c_str());
	ImGui::End();
	
	
	

	
	for (Layer* layer : mLayers)
		layer->OnImGuiRender(); ;
	mGuiLayer->End();
}
