#include <Kaiser.h>

#include "imgui.h"


class ExampleLayer : public Kaiser::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//KS_INFO("ExampleLayer::Update");

	}

	void OnEvent(Kaiser::Event& event) override
	{
		if (event.GetEventType() == Kaiser::EventType::KeyPressed)
		{
			Kaiser::KeyPressedEvent& e = (Kaiser::KeyPressedEvent&)event;
			//KS_TRACE("{0}", (char)e.GetKey());
		}
	}

	void OnImGuiRender() override
	{

	}
};

class Sandbox : public Kaiser::Application
{
public:
	Sandbox()
	{
		PushLayer(knew ExampleLayer());
	}

	~Sandbox()
	{

	}


	
};

Kaiser::Application* Kaiser::CreateApplication()
{

	
	return new Sandbox();
}