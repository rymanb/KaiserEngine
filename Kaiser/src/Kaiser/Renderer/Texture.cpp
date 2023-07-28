#include "stdafx.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Kaiser
{
	Ref<Texture2D> Texture2D::Create(const std::string& path, bool srgb)
	{
		switch (Renderer::API())
		{
		case RenderAPI::API::None:    KS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return  CreateRef<OpenGLTexture2D>(path, srgb);
		}

		KS_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(const std::string& path)
	{
		switch (Renderer::API())
		{
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLTextureCube>(path);
		}
		return nullptr;
	}


	uint32_t Texture::GetBPP(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB:    return 3;
		case TextureFormat::RGBA:   return 4;
		}
		return 0;
	}

	uint32_t Texture::CalculateMipMapCount(uint32_t width, uint32_t height)
	{
		uint32_t levels = 1;
		while ((width | height) >> levels)
			levels++;

		return levels;
	}
}
