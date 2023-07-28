#pragma once

#include "Kaiser/Renderer/Texture.h"
#include "Kaiser/Core/Buffer.h"


namespace Kaiser
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, bool srgb);
		virtual ~OpenGLTexture2D();

		virtual TextureFormat GetFormat() const override { return mFormat; }
		virtual uint32_t GetWidth() const override { return mWidth; }
		virtual uint32_t GetHeight() const override { return mHeight; }

		virtual uint32_t GetMipLevelCount() const override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual Buffer GetWriteableBuffer() override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind() const;

		virtual uint32_t GetID() const override { return mId; }
		virtual bool Loaded() const override { return mLoaded; }
		
		virtual bool operator==(const Texture& other) const override
		{
			return mId == ((OpenGLTexture2D&)other).mId;
		}

		virtual const std::string& GetPath() const override { return mPath; }
	private:
		std::string mPath;
		TextureFormat mFormat;
		TextureWrap mWrap = TextureWrap::Clamp;
		uint32_t mWidth, mHeight;
		uint32_t mId;
		
		Buffer mData;
		
		bool mLoaded;
		std::string mFilePath;
	};
	
	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(const std::string& path);
		virtual ~OpenGLTextureCube();

		virtual void Bind(uint32_t slot = 0) const;
		virtual void Unbind() const;

		virtual uint32_t GetMipLevelCount() const override { return 0; }

		virtual TextureFormat GetFormat() const { return m_Format; }
		virtual unsigned int GetWidth() const { return m_Width; }
		virtual unsigned int GetHeight() const { return m_Height; }

		virtual const std::string& GetPath() const override { return m_FilePath; }

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTextureCube&)other).m_RendererID;
		}

		virtual uint32_t GetID() const override { return m_RendererID; }
	private:
		uint32_t m_RendererID;
		TextureFormat m_Format;
		unsigned int m_Width, m_Height;

		unsigned char* m_ImageData;

		std::string m_FilePath;
	};
		
}