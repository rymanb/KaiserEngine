#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Kaiser/Renderer/Shader.h"


#include "Kaiser/Core/Trace.h"

typedef unsigned int GLenum;



namespace Kaiser
{
	
	static GLenum ShaderTypeFromString(const std::string& type);

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void UploadUniformBuffer(const UniformBufferBase& uniformBuffer) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& Name() const override { return mName; }

		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
		void UploadUniformFloat(const std::string& name, const float& value);
		void UploadUniformVec2(const std::string& name, const glm::vec2& vector);
		void UploadUniformVec3(const std::string& name, const glm::vec3& vector);
		void UploadUniformVec4(const std::string& name, const glm::vec4& vector);
		
		void UploadUniformInt(const std::string& name, const int& value);

		virtual void SetFloat(const std::string& name, float value);
		virtual void SetInt(const std::string& name, int value);
		virtual void SetMat4(const std::string& name, const glm::mat4& value);
		

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);

		typedef enum class SupportedShaders
		{
			Vertex = 0,
			Fragment,
			Max
			
		};
		
		uint32_t mID;
		std::string mName;
	};
}