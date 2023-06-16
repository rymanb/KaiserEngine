#include <Kaiser.h>

#include "imgui.h"

using namespace Kaiser;

static float fov = 60.0f;


class ExampleLayer : public Kaiser::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

		

		camera.SetOrthoProjection(3, 1.8, -1, 1);

		// there is a object at (0,0,0) create a camera that can see it
		//camera.SetPerspectiveProjection(glm::radians(fov), 500, 500, 0.0f, 100.0f);
		
		// Vertex Array Object
		vertexArray.reset(VertexArray::Create());

		// NDC coords -1 to 1
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		// Vertex Buffer Object
		std::shared_ptr<VertexBuffer> vertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));


		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		BufferLayout layout =
		{
			{ShaderDataType::Vec3, "a_Position"},
			{ShaderDataType::Vec4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);

		vertexArray->SetVertexBuffer(vertexBuffer);


		// Index Buffer Object
		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> indexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertexArray->SetIndexBuffer(indexBuffer);

		squareVA = std::shared_ptr<VertexArray>(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ShaderDataType::Vec3, "a_Position"}
			});

		squareVA->SetVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<IndexBuffer> squareIB = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		squareVA->SetIndexBuffer(squareIB);


		std::string vertSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;

		out vec3 position;
		out vec4 v_color;

		void main()
		{
			position = a_Position;
			v_color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

		}



	)";

		std::string fragSrc = R"(
		#version 330 core

		out vec4 color;
		in vec3 position;
		in vec4 v_color;
		

		void main()
		{
			color = v_color;
		}



	)";

		shader.reset(new Shader(vertSrc, fragSrc));

		std::string vertSrc2 = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		out vec3 position;
		out vec4 v_color;

		uniform mat4 u_ViewProjection;

		void main()
		{
			position = a_Position;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

		}



	)";

		std::string fragSrc2 = R"(
		#version 330 core

		out vec4 color;
		in vec3 position;

		

		void main()
		{
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}



	)";

		shader2.reset(new Shader(vertSrc2, fragSrc2));





	}

	void OnUpdate() override
	{
		this->mActiveScene = Engine::Instance().Get<SceneManager>()->GetScene("test");
		// update active scene

		static int counter = 0;
		while (counter++ < 10)
		{
			//Entity ent = mActiveScene->AddEntity("Entity: " + std::to_string(counter));
			auto ent = mActiveScene->CreateEntity();
			ent.AddComponent<Test>();
			//mActiveScene->AddComponent<Test>(entt);
			
		}

		mActiveScene->Update();
		
		static glm::vec3 position = { 0.0f, 0.0f, 1.0f };
		static glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		float dt = 0.2;

		if (Input::IsKeyPressed(KeyCode::A))
			position.x -= 0.1f * dt;
		if (Input::IsKeyPressed(KeyCode::D))
			position.x += 0.1f * dt;
		if (Input::IsKeyPressed(KeyCode::W))
			position.z -= 0.1f * dt;
		if (Input::IsKeyPressed(KeyCode::S))
			position.z += 0.1f * dt;
		if (Input::IsKeyPressed(KeyCode::Q))
			position.y -= 0.1f * dt;
		if (Input::IsKeyPressed(KeyCode::E))
			position.y += 0.1f * dt;

		if (Input::IsKeyPressed(KeyCode::Left))
			rotation.y += 0.1f ;
		if (Input::IsKeyPressed(KeyCode::Right))
			rotation.y -= 0.1f ; 
		if (Input::IsKeyPressed(KeyCode::Up))
			rotation.x += 0.1f;
		if (Input::IsKeyPressed(KeyCode::Down))
			rotation.x -= 0.1f;
		
		

		camera.SetPosition(position);
		camera.SetRotation(45.0f);



		//KS_INFO("ExampleLayer::Update");
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		RenderCommand::Clear();

		auto& view = camera.GetViewProjection();

		Renderer::BeginScene(camera);

		Renderer::Submit(shader2, squareVA);


		Renderer::Submit(shader, vertexArray);

		Renderer::EndScene();
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
		ImGui::Begin("fov");
		ImGui::DragFloat("fov", &fov);
		ImGui::End();
	}

private:
	std::shared_ptr<Kaiser::VertexArray> vertexArray;
	std::shared_ptr<Kaiser::Shader> shader;


	std::shared_ptr<Kaiser::VertexArray> squareVA;
	std::shared_ptr <Kaiser::Shader> shader2;

	Camera camera;
};

class Sandbox : public Kaiser::Application
{
public:
	Sandbox()
	{
		IEngine& engine = Engine::Instance();
		engine.Add<SceneManager>();

		
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}


	
};

Kaiser::Application* Kaiser::CreateApplication()
{

	
	return new Sandbox();
}