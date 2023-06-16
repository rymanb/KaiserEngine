#pragma once

#include "stdafx.h"
#include "Kaiser/Trace.h"

namespace Kaiser
{

	enum class ShaderDataType
	{
		None = 0,
		Float, Vec2, Vec3, Vec4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Vec2:  return 4 * 2;
			case ShaderDataType::Vec3:  return 4 * 3;
			case ShaderDataType::Vec4:  return 4 * 4;
			case ShaderDataType::Mat3:  return 4 * 3 * 3;
			case ShaderDataType::Mat4:  return 4 * 4 * 4;
			case ShaderDataType::Int:	return 4;
			case ShaderDataType::Int2:  return 4 * 2;
			case ShaderDataType::Int3:  return 4 * 3;
			case ShaderDataType::Int4:  return 4 * 4;
			case ShaderDataType::Bool:  return 1;
			
		}
		
		KS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}

		uint32_t GetElementCount() const
		{
			switch (Type)
			{
				case Kaiser::ShaderDataType::Float:
					return 1;
				case Kaiser::ShaderDataType::Vec2:
					return 2;
				case Kaiser::ShaderDataType::Vec3:
					return 3;
				case Kaiser::ShaderDataType::Vec4:
					return 4;
				case Kaiser::ShaderDataType::Mat3:
					return 3 * 3;
				case Kaiser::ShaderDataType::Mat4:
					return 4 * 4;
				case Kaiser::ShaderDataType::Int:
					return 0;
				case Kaiser::ShaderDataType::Int2:
					return 2;
				case Kaiser::ShaderDataType::Int3:
					return 3;
				case Kaiser::ShaderDataType::Int4:
					return 4;
				case Kaiser::ShaderDataType::Bool:
					return 1;
				default:
					return 0;
			}

			KS_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
		
	};

	class BufferLayout
	{
	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : mElements(elements) 
		{
			CalculateOffsetsAndStride();
		}
		
		inline const std::vector<BufferElement>& GetElements() const { return mElements; }

		inline uint32_t GetStride() const { return mStride; }
		
		std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }
		
	private:

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			mStride = 0;
			for (auto& e : mElements)
			{
				e.Offset = offset;
				offset += e.Size;
				mStride += e.Size;
			}
		}
		
		std::vector<BufferElement> mElements;
		uint32_t mStride = 0;
	};

	
	class Buffer
	{
	public:
		virtual ~Buffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	class VertexBuffer : public Buffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, size_t size);
	};

	class IndexBuffer : public Buffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;


		static IndexBuffer* Create(uint32_t* indices, size_t count);
	};
}