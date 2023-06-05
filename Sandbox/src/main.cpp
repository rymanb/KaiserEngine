#include <Kaiser.h>

class ExampleLayer : public Kaiser::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		KS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Kaiser::Event& event) override
	{
		KS_TRACE("{0}", event);
	}
};

class Sandbox : public Kaiser::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Kaiser::ImGuiLayer());
	}

	~Sandbox()
	{

	}

	
};

Kaiser::Application* Kaiser::CreateApplication()
{

	
	return new Sandbox();
}