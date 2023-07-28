#include "stdafx.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>
#include "Kaiser/Renderer/Renderer.h"

namespace Kaiser
{

	static GLenum KaiserToOpenGLTextureFormat(TextureFormat format)
	{
		switch (format)
		{
		case Kaiser::TextureFormat::RGB:     return GL_RGB;
		case Kaiser::TextureFormat::RGBA:    return GL_RGBA;
		}
		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, bool srgb) : mPath(path)
	{
		//int width, height, channels;
		//KS_CORE_INFO("Loading texture {0}, srgb={1}", path, srgb);
		//stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, srgb ? STBI_rgb : STBI_rgb_alpha);


		//mWidth = width;
		//mHeight = height;
		//GLenum internalFormat = 0, dataFormat = 0;
		//if (channels == 4)
		//{
		//	internalFormat = GL_RGBA8;
		//	dataFormat = GL_RGBA;
		//}
		//else if (channels == 3)
		//{
		//	internalFormat = GL_RGB8;
		//	dataFormat = GL_RGB;
		//}
		//else if (channels == 2)
		//{
		//	internalFormat = GL_RG8;
		//	dataFormat = GL_RG;
		//}
		//else if (channels == 1)
		//{
		//	internalFormat = GL_R8;
		//	dataFormat = GL_RED;
		//}
		//else
		//{
		//	KS_CORE_ASSERT(false, "Unsupported number of channels!");
		//}

		//Renderer::Submit([=] {
		//	if (srgb)
		//	{
		//		glCreateTextures(GL_TEXTURE_2D, 1, &mId);
		//		int levels = CalculateMipMapCount(mWidth, mHeight);
		//		KS_CORE_INFO("Creating srgb texture width {0} mips", levels);
		//		glTextureStorage2D(mId, levels, GL_SRGB8, mWidth, mHeight);
		//		glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
		//		glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//		glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
		//		glGenerateTextureMipmap(mId);
		//	}
		//	else
		//	{
		//		glGenTextures(1, &mId);
		//		glBindTexture(GL_TEXTURE_2D, mId);

		//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//		glTexImage2D(GL_TEXTURE_2D, 0, KaiserToOpenGLTextureFormat(mFormat), mWidth, mHeight, 0, srgb ? GL_SRGB8 : KaiserToOpenGLTextureFormat(mFormat), GL_UNSIGNED_BYTE, data);
		//		glGenerateMipmap(GL_TEXTURE_2D);

		//		glBindTexture(GL_TEXTURE_2D, 0);
		//	}
		//	stbi_image_free(data);
		//	});

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		KS_CORE_ASSERT(data, "Failed to load image!");
		mWidth = width;
		mHeight = height;
		
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 2)
		{
			internalFormat = GL_RG8;
			dataFormat = GL_RG;
		}
		else if (channels == 1)
		{
			internalFormat = GL_R8;
			dataFormat = GL_RED;
		}
		else
		{
			KS_CORE_ASSERT(false, "Unsupported number of channels!");
		}

		Renderer::Submit([=] {

			KS_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &mId);
			glTextureStorage2D(mId, 1, internalFormat, mWidth, mHeight);

			glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
			});
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &mId);
	}

	uint32_t OpenGLTexture2D::GetMipLevelCount() const
	{
		return Texture::CalculateMipMapCount(mWidth, mHeight);
	}

	void OpenGLTexture2D::Resize(uint32_t width, uint32_t height)
	{
		mData.Allocate(width * height * GetBPP(mFormat));
		
		mData.ZeroInitialize();
	}

	Kaiser::Buffer OpenGLTexture2D::GetWriteableBuffer()
	{
		return mData;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		Renderer::Submit([=] {
			glBindTextureUnit(slot, mId);
			});
	}

	void OpenGLTexture2D::Unbind() const
	{
		Renderer::Submit([] {
			glBindTexture(GL_TEXTURE_2D, 0);
			});
	}

	//////////////////////////////////////////////////////////////////////////////////
	// TextureCube
	//////////////////////////////////////////////////////////////////////////////////


	OpenGLTextureCube::OpenGLTextureCube(const std::string& path)
		: m_FilePath(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(false);
		m_ImageData = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);

		m_Width = width;
		m_Height = height;
		m_Format = TextureFormat::RGB;

		unsigned int faceWidth = m_Width / 4;
		unsigned int faceHeight = m_Height / 3;
		KS_CORE_ASSERT(faceWidth == faceHeight, "Non-square faces!");

		std::array<unsigned char*, 6> faces;
		for (size_t i = 0; i < faces.size(); i++)
			faces[i] = new unsigned char[faceWidth * faceHeight * 3]; // 3 BPP

		int faceIndex = 0;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + i * faceWidth;
					faces[faceIndex][(x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 0];
					faces[faceIndex][(x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 1];
					faces[faceIndex][(x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 2];
				}
			}
			faceIndex++;
		}

		for (size_t i = 0; i < 3; i++)
		{
			// Skip the middle one
			if (i == 1)
				continue;

			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + i * faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + faceWidth;
					faces[faceIndex][(x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 0];
					faces[faceIndex][(x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 1];
					faces[faceIndex][(x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 2];
				}
			}
			faceIndex++;
		}

		Renderer::Submit([=]() {
			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			glTextureParameterf(m_RendererID, GL_TEXTURE_MAX_ANISOTROPY, RenderAPI::GetCapabilities().MaxAnisotropy);

			auto format = KaiserToOpenGLTextureFormat(m_Format);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[2]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[0]);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[4]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[5]);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[1]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[3]);

			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			for (size_t i = 0; i < faces.size(); i++)
				delete[] faces[i];

			stbi_image_free(m_ImageData);
			});
	}

	OpenGLTextureCube::~OpenGLTextureCube()
	{
		auto self = this;
		Renderer::Submit([this]() {
			glDeleteTextures(1, &m_RendererID);
			});
	}

	void OpenGLTextureCube::Bind(uint32_t slot) const
	{
		Renderer::Submit([this, slot]() {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
			});
	}

	void OpenGLTextureCube::Unbind() const
	{
		Renderer::Submit([this]() {
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			});
	}

}