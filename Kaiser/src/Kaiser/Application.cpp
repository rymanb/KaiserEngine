#include "stdafx.h"
#include "Application.h"

#include "Kaiser/Trace.h"

#include <glad/glad.h>
#include "Input.h"


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

	guiLayer = new ImGuiLayer();
	PushOverlay(guiLayer);

	// Vertex Array Object
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	// Vertex Buffer Object
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	// NDC coords -1 to 1
	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	// Index Buffer Object
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	unsigned int indices[3] = { 0, 1, 2 };
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vertSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		out vec3 position;

		void main()
		{
			gl_Position = vec4(a_Position,1.0);
			position = vec3(a_Position * 0.5 + 0.5);
		}



	)";

	std::string fragSrc = R"(
		#version 330 core

		out vec4 color;
		in vec3 position;
		

		void main()
		{
			color = vec4(position, 1.0);
		}



	)";

	shader.reset(new Shader(vertSrc, fragSrc));
}

Kaiser::Application::~Application()
{
}

void Kaiser::Application::Run()
{


	while (running)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Bind();
		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		shader->Unbind();
		
		for (Layer* layer : layers)
			layer->OnUpdate();

		guiLayer->Begin();
		for (Layer* layer : layers)
			layer->OnImGuiRender();
		guiLayer->End();

		
		window->OnUpdate();
	}
}

void Kaiser::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

	//KS_CORE_TRACE("{0}", e);
	
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
