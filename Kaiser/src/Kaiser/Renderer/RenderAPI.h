#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Kaiser
{
	enum class PrimitiveType
	{
		None = 0, Triangles, Lines
	};

	struct RenderAPICapabilities
	{
		std::string Vendor;
		std::string Renderer;
		std::string Version;

		int MaxSamples;
		float MaxAnisotropy;
	};


	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		static RenderAPICapabilities& GetCapabilities()
		{
			static RenderAPICapabilities capabilities;
			return capabilities;
		}

		virtual void Init() = 0;


		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(uint32_t count,  bool depthTest) = 0;

		inline static API GetAPI() { return sApi; }

	private:
		static API sApi;
	};

}