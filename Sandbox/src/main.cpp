#include <Kaiser.h>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"


using namespace Kaiser;

static float fov = 60.0f;


class ExampleLayer : public Kaiser::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		camera = Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 1000.0f));
		auto texShader = mShaderManager.Load("Assets/Shaders/Texture.glsl");

		
		
		auto pbr = mShaderManager.Load("Assets/Shaders/simplepbr.glsl");
		auto quadShader = mShaderManager.Load("Assets/Shaders/quad.glsl");
		auto hdr = mShaderManager.Load("Assets/Shaders/hdr.glsl");
		mesh = CreateRef<Mesh>("Assets/Meshes/cerberus.fbx");
		sphere = CreateRef<Mesh>("Assets/Models/Sphere.fbx");
		gun = CreateRef<Mesh>("Assets/Models/Granade.fbx");

		// Create Texture
		texture = Texture2D::Create("Checkerboard.png");


		

		//m_AlbedoInput.TextureMap = Texture2D::Create("Assets/Textures/grenade_Base_color.png");
		//m_NormalInput.TextureMap = Texture2D::Create("Assets/Textures/grenade_Normal_OpenGL.png");
		//m_MetalnessInput.TextureMap = Texture2D::Create("Assets/Textures/grenade_Metallic.png");
		//m_RoughnessInput.TextureMap = Texture2D::Create("Assets/Textures/grenade_Roughness.png");
		//ao = Texture2D::Create("Assets/Textures/grenade_Mixed_AO.png");



		m_EnvironmentCubeMap = TextureCube::Create("Assets/Textures/Environments/Arches_E_PineTree_Radiance.tga");
		m_EnvironmentIrradiance = (TextureCube::Create("Assets/Textures/Environments/Arches_E_PineTree_Irradiance.tga"));
		m_BRDFLUT = Texture2D::Create("Assets/Textures/BRDF_LUT.tga");


		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		fbSpec.Format = FramebufferFormat::RGBA16F;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		fbSpec.Format = FramebufferFormat::RGBA8;
		m_FinalPresentBuffer = Framebuffer::Create(fbSpec);

		// Create Quad
		float x = -1, y = -1;
		float width = 2, height = 2;
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec2 TexCoord;
		};

		QuadVertex data[4];

		data[0].Position = glm::vec3(x, y, 0);
		data[0].TexCoord = glm::vec2(0, 0);

		data[1].Position = glm::vec3(x + width, y, 0);
		data[1].TexCoord = glm::vec2(1, 0);

		data[2].Position = glm::vec3(x + width, y + height, 0);
		data[2].TexCoord = glm::vec2(1, 1);

		data[3].Position = glm::vec3(x, y + height, 0);
		data[3].TexCoord = glm::vec2(0, 1);

		m_VertexBuffer.reset(VertexBuffer::Create(data, 4 * sizeof(QuadVertex)));

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0, };
		m_IndexBuffer = IndexBuffer::Create(indices, 6 * sizeof(uint32_t));

		m_Light.Direction = { -0.5f, -0.5f, 1.0f };
		m_Light.Radiance = { 1.0f, 1.0f, 1.0f };
	}

	void OnUpdate() override
	{
		using namespace glm;
		camera.OnUpdate();
		auto viewProjection = camera.GetViewProjection();

		static glm::vec3 position = { 0.0f, 0.0f, 1.0f };
		static glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		auto m_HDRShader = mShaderManager.Get("hdr");
		auto m_SimplePBRShader = mShaderManager.Get("simplepbr");
		auto m_QuadShader = mShaderManager.Get("quad");

		m_Framebuffer->Bind();

		Renderer::Clear({ 0.1f, 0.1f, 0.1f, 0.1f });


		Renderer::BeginScene(camera);

		UniformBufferDeclaration<sizeof(mat4), 1> quadShaderUB;
		quadShaderUB.Push("u_InverseVP", inverse(camera.GetViewProjection()));
		m_QuadShader->UploadUniformBuffer(quadShaderUB);

		
		m_QuadShader->Bind();
		m_EnvironmentIrradiance->Bind(0);
		//m_SimplePBRShader->SetInt("u_EnvIrradianceTex", 0);
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
		Renderer::DrawIndexed(m_IndexBuffer->GetCount(), false);

		m_EnvironmentIrradiance->Unbind();
		

		UniformBufferDeclaration<sizeof(mat4) * 2 + sizeof(vec3) * 4 + sizeof(float) * 8, 14> simplePbrShaderUB;
		simplePbrShaderUB.Push("u_ViewProjectionMatrix", camera.GetViewProjection());
		simplePbrShaderUB.Push("u_ModelMatrix", mat4(1.0f));
		simplePbrShaderUB.Push("u_AlbedoColor", m_AlbedoInput.Color);
		simplePbrShaderUB.Push("u_Metalness", m_MetalnessInput.Value);
		simplePbrShaderUB.Push("u_Roughness", m_RoughnessInput.Value);
		simplePbrShaderUB.Push("lights.Direction", m_Light.Direction);
		simplePbrShaderUB.Push("lights.Radiance", m_Light.Radiance * m_LightMultiplier);
		simplePbrShaderUB.Push("u_CameraPosition", camera.GetPosition());
		simplePbrShaderUB.Push("u_RadiancePrefilter", m_RadiancePrefilter ? 1.0f : 0.0f);
		simplePbrShaderUB.Push("u_AlbedoTexToggle", m_AlbedoInput.UseTexture ? 1.0f : 0.0f);
		simplePbrShaderUB.Push("u_NormalTexToggle", m_NormalInput.UseTexture ? 1.0f : 0.0f);
		simplePbrShaderUB.Push("u_MetalnessTexToggle", m_MetalnessInput.UseTexture ? 1.0f : 0.0f);
		simplePbrShaderUB.Push("u_RoughnessTexToggle", m_RoughnessInput.UseTexture ? 1.0f : 0.0f);
		simplePbrShaderUB.Push("u_EnvMapRotation", m_EnvMapRotation);
		m_SimplePBRShader->UploadUniformBuffer(simplePbrShaderUB);

		m_SimplePBRShader->Bind();
		m_EnvironmentCubeMap->Bind(10);
		m_SimplePBRShader->SetInt("u_EnvRadianceTex", 10);
		m_EnvironmentIrradiance->Bind(11);
		m_SimplePBRShader->SetInt("u_EnvIrradianceTex", 11);
		m_BRDFLUT->Bind(15);
		m_SimplePBRShader->SetInt("u_BRDFLUTTexture", 15);


		
		if (m_AlbedoInput.TextureMap)
		{
			m_AlbedoInput.TextureMap->Bind(1);
			m_SimplePBRShader->SetInt("u_AlbedoTexture", 1);
		}
		if (m_NormalInput.TextureMap)
		{
			m_NormalInput.TextureMap->Bind(2);
			m_SimplePBRShader->SetInt("u_NormalTexture", 2);
		}
		if (m_MetalnessInput.TextureMap)
		{
			m_MetalnessInput.TextureMap->Bind(3);
			m_SimplePBRShader->SetInt("u_MetalnessTexture", 3);
		}
		if (m_RoughnessInput.TextureMap)
		{
			m_RoughnessInput.TextureMap->Bind(4);
			m_SimplePBRShader->SetInt("u_RoughnessTexture", 4);
		}
		
		if (spheres == true)
		{
			// Metals
			float roughness = 0.0f;
			float x = -88.0f;
			for (int i = 0; i < 8; i++)
			{
				m_SimplePBRShader->SetMat4("u_ModelMatrix", translate(mat4(1.0f), vec3(x, 0.0f, 0.0f)));
				m_SimplePBRShader->SetFloat("u_Roughness", roughness);
				m_SimplePBRShader->SetFloat("u_Metalness", 1.0f);
				sphere->Render();

				roughness += 0.15f;
				x += 22.0f;
			}

			// Dielectrics
			roughness = 0.0f;
			x = -88.0f;
			for (int i = 0; i < 8; i++)
			{
				m_SimplePBRShader->SetMat4("u_ModelMatrix", translate(mat4(1.0f), vec3(x, 22.0f, 0.0f)));
				m_SimplePBRShader->SetFloat("u_Roughness", roughness);
				m_SimplePBRShader->SetFloat("u_Metalness", 0.0f);
				sphere->Render();

				roughness += 0.15f;
				x += 22.0f;
			}
		}
		else
			gun->Render();
		
		m_EnvironmentCubeMap->Unbind();
		m_EnvironmentIrradiance->Unbind();

		m_Framebuffer->Unbind();

		m_FinalPresentBuffer->Bind();
		m_HDRShader->Bind();
		m_HDRShader->SetFloat("u_Exposure", m_Exposure);
		m_Framebuffer->BindTexture();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
		Renderer::DrawIndexed(m_IndexBuffer->GetCount(), false);
		m_FinalPresentBuffer->Unbind();
	}

	void OnEvent(Kaiser::Event& event) override
	{
		if (event.GetEventType() == Kaiser::EventType::KeyPressed)
		{
			Kaiser::KeyPressedEvent& e = (Kaiser::KeyPressedEvent&)event;
			//KS_TRACE("{0}", (char)e.GetKey());
		}

		camera.OnEvent(event);
	}

	void OnImGuiRender() override
	{
		static bool p_open = true;

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		// Editor Panel ------------------------------------------------------------------------------
		ImGui::Begin("Settings");

		ImGui::RadioButton("Spheres", (int*)&spheres, (int)true);
		ImGui::SameLine();
		ImGui::RadioButton("Model", (int*)&spheres, (int)false);

		ImGui::SliderFloat3("Light Dir", glm::value_ptr(m_Light.Direction), -1, 1);
		ImGui::ColorEdit3("Light Radiance", glm::value_ptr(m_Light.Radiance));
		ImGui::SliderFloat("Light Multiplier", &m_LightMultiplier, 0.0f, 5.0f);
		ImGui::SliderFloat("Exposure", &m_Exposure, 0.0f, 10.0f);
		auto cameraForward = camera.GetForwardDirection();
		ImGui::Text("Camera Forward: %.2f, %.2f, %.2f", cameraForward.x, cameraForward.y, cameraForward.z);


		ImGui::Separator();

		ImGui::Text("Shader Parameters");
		ImGui::Checkbox("Radiance Prefiltering", &m_RadiancePrefilter);
		ImGui::SliderFloat("Env Map Rotation", &m_EnvMapRotation, -360.0f, 360.0f);

		ImGui::Separator();

		// Textures ------------------------------------------------------------------------------
		{
			// Albedo
			if (ImGui::CollapsingHeader("Albedo", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::Image(m_AlbedoInput.TextureMap ? (void*)m_AlbedoInput.TextureMap->GetID() : (void*)texture->GetID(), ImVec2(64, 64));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
					if (m_AlbedoInput.TextureMap)
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
						ImGui::TextUnformatted(m_AlbedoInput.TextureMap->GetPath().c_str());
						ImGui::PopTextWrapPos();
						ImGui::Image((void*)m_AlbedoInput.TextureMap->GetID(), ImVec2(384, 384));
						ImGui::EndTooltip();
					}
					if (ImGui::IsItemClicked())
					{
						std::string filename = Application::Get().OpenFile("");
						if (filename != "")
							m_AlbedoInput.TextureMap=(Texture2D::Create(filename, m_AlbedoInput.SRGB));
					}
				}
				ImGui::SameLine();
				ImGui::BeginGroup();
				ImGui::Checkbox("Use##AlbedoMap", &m_AlbedoInput.UseTexture);
				if (ImGui::Checkbox("sRGB##AlbedoMap", &m_AlbedoInput.SRGB))
				{
					if (m_AlbedoInput.TextureMap)
						m_AlbedoInput.TextureMap=(Texture2D::Create(m_AlbedoInput.TextureMap->GetPath(), m_AlbedoInput.SRGB));
				}
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::ColorEdit3("Color##Albedo", glm::value_ptr(m_AlbedoInput.Color), ImGuiColorEditFlags_NoInputs);
			}
		}
		{
			// Normals
			if (ImGui::CollapsingHeader("Normals", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::Image(m_NormalInput.TextureMap ? (void*)m_NormalInput.TextureMap->GetID() : (void*)texture->GetID(), ImVec2(64, 64));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
					if (m_NormalInput.TextureMap)
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
						ImGui::TextUnformatted(m_NormalInput.TextureMap->GetPath().c_str());
						ImGui::PopTextWrapPos();
						ImGui::Image((void*)m_NormalInput.TextureMap->GetID(), ImVec2(384, 384));
						ImGui::EndTooltip();
					}
					if (ImGui::IsItemClicked())
					{
						std::string filename = Application::Get().OpenFile("");
						if (filename != "")
							m_NormalInput.TextureMap=(Texture2D::Create(filename));
					}
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##NormalMap", &m_NormalInput.UseTexture);
			}
		}
		{
			// Metalness
			if (ImGui::CollapsingHeader("Metalness", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::Image(m_MetalnessInput.TextureMap ? (void*)m_MetalnessInput.TextureMap->GetID() : (void*)texture->GetID(), ImVec2(64, 64));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
					if (m_MetalnessInput.TextureMap)
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
						ImGui::TextUnformatted(m_MetalnessInput.TextureMap->GetPath().c_str());
						ImGui::PopTextWrapPos();
						ImGui::Image((void*)m_MetalnessInput.TextureMap->GetID(), ImVec2(384, 384));
						ImGui::EndTooltip();
					}
					if (ImGui::IsItemClicked())
					{
						std::string filename = Application::Get().OpenFile("");
						if (filename != "")
							m_MetalnessInput.TextureMap=(Texture2D::Create(filename));
					}
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##MetalnessMap", &m_MetalnessInput.UseTexture);
				ImGui::SameLine();
				ImGui::SliderFloat("Value##MetalnessInput", &m_MetalnessInput.Value, 0.0f, 1.0f);
			}
		}
		{
			// Roughness
			if (ImGui::CollapsingHeader("Roughness", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::Image(m_RoughnessInput.TextureMap ? (void*)m_RoughnessInput.TextureMap->GetID() : (void*)texture->GetID(), ImVec2(64, 64));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
					if (m_RoughnessInput.TextureMap)
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
						ImGui::TextUnformatted(m_RoughnessInput.TextureMap->GetPath().c_str());
						ImGui::PopTextWrapPos();
						ImGui::Image((void*)m_RoughnessInput.TextureMap->GetID(), ImVec2(384, 384));
						ImGui::EndTooltip();
					}
					if (ImGui::IsItemClicked())
					{
						std::string filename = Application::Get().OpenFile("");
						if (filename != "")
							m_RoughnessInput.TextureMap=(Texture2D::Create(filename));
					}
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##RoughnessMap", &m_RoughnessInput.UseTexture);
				ImGui::SameLine();
				ImGui::SliderFloat("Value##RoughnessInput", &m_RoughnessInput.Value, 0.0f, 1.0f);
			}
		}

		ImGui::Separator();

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportSize = ImGui::GetContentRegionAvail();
		m_Framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		m_FinalPresentBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		camera.SetProjectionMatrix(glm::perspectiveFov(glm::radians(45.0f), viewportSize.x, viewportSize.y, 0.1f, 10000.0f));
		ImGui::Image((void*)m_FinalPresentBuffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (opt_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 opt_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (opt_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  opt_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: NoResize", "", (opt_flags & ImGuiDockNodeFlags_NoResize) != 0))                opt_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: PassthruDockspace", "", (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))       opt_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (opt_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          opt_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				ImGui::Separator();
				if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
					p_open = false;
				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}

		ImGui::End();
		
	}

private:
	bool spheres = false;
	Ref<VertexArray> squareVA;
	Ref<VertexArray> cubeVA;
	Ref<Mesh> sphere;
	Ref<Mesh> gun;
	Ref<Mesh> mesh;

	Ref<Texture2D> texture;
	Ref<Texture2D> color, normal, metallic, roughness;
	Ref<Texture2D> m_BRDFLUT;

	Camera camera;

	glm::vec3 squarePosition = { 0.0f, 0.0f, 0.0f };

	glm::vec3 m_squareColor = { 0.2f, 0.3f, 0.8f };

	ShaderManager mShaderManager;


	struct AlbedoInput
	{
		glm::vec3 Color = { 0.972f, 0.96f, 0.915f }; // Silver, from https://docs.unrealengine.com/en-us/Engine/Rendering/Material
		Ref<Texture2D> TextureMap;
		bool SRGB = true;
		bool UseTexture = false;
	};
	AlbedoInput m_AlbedoInput;

	struct NormalInput
	{
		Ref<Texture2D> TextureMap;
		bool UseTexture = false;
	};
	NormalInput m_NormalInput;

	struct MetalnessInput
	{
		float Value = 1.0f;
		Ref<Texture2D> TextureMap;
		bool UseTexture = false;
	};
	MetalnessInput m_MetalnessInput;

	struct RoughnessInput
	{
		float Value = 0.5f;
		Ref<Texture2D> TextureMap;
		bool UseTexture = false;
	};
	RoughnessInput m_RoughnessInput;

	Ref<Framebuffer> m_Framebuffer, m_FinalPresentBuffer;

	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;
	Ref<TextureCube> m_EnvironmentCubeMap, m_EnvironmentIrradiance;


	struct Light
	{
		glm::vec3 Direction;
		glm::vec3 Radiance;
	};
	Light m_Light;
	float m_LightMultiplier = 0.3f;

	// PBR params
	float m_Exposure = 1.0f;

	bool m_RadiancePrefilter = false;

	float m_EnvMapRotation = 0.0f;
};



class Sandbox : public Kaiser::Application
{
public:
	Sandbox()
	{		
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