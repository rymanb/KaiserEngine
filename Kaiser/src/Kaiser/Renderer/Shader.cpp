#include "stdafx.h"
#include "Shader.h"


#include "Kaiser/Core/Trace.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Kaiser
{

	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::API())
		{
		case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filePath);
		}

		KS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::API())
		{
		case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		KS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderManager::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->Name();
		Add(name, shader);
	}

	void ShaderManager::Add(const std::string& name, const Ref<Shader>& shader)
	{
		KS_CORE_ASSERT(!Exists(name), "Shader already exists!");
		mShaders[name] = shader;
	}

	Ref<Shader> ShaderManager::Get(const std::string& name)
	{
		KS_CORE_ASSERT(Exists(name), "Shader not found!");
		return mShaders[name];
	}

	bool ShaderManager::Exists(const std::string& name) const
	{
		return mShaders.find(name) != mShaders.end();
	}

	Ref<Shader> ShaderManager::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderManager::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

}