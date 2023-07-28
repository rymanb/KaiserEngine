#include "stdafx.h"
#include "OpenGLShader.h"


#include <fstream>
#include <glad/glad.h>
#include "Kaiser/Core/Trace.h"
#include "Kaiser/Renderer/Renderer.h"

Kaiser::OpenGLShader::OpenGLShader(const std::string& filePath)
{
	std::string source = ReadFile(filePath);
	auto shaderSources = PreProcess(source);
	Compile(shaderSources);

	// Get name from filepath
	auto lastSlash = filePath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = filePath.rfind('.');
	auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
	mName = filePath.substr(lastSlash, count);
}

Kaiser::OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : mName(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSource;
	sources[GL_FRAGMENT_SHADER] = fragmentSource;
	Compile(sources);
}

Kaiser::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(mID);
}

void Kaiser::OpenGLShader::UploadUniformBuffer(const UniformBufferBase& uniformBuffer)
{
	for (unsigned int i = 0; i < uniformBuffer.GetUniformCount(); i++)
	{
		const UniformDecl& decl = uniformBuffer.GetUniforms()[i];
		switch (decl.Type)
		{
		case UniformType::Float:
		{
			const std::string& name = decl.Name;
			float value = *(float*)(uniformBuffer.GetBuffer() + decl.Offset);

			UploadUniformFloat(name, value);
			break;
		}
		case UniformType::Float2:
		{
			const std::string& name = decl.Name;
			glm::vec2 value = *(glm::vec2*)(uniformBuffer.GetBuffer() + decl.Offset);

			UploadUniformVec2(name, value);
			break;

		}
		case UniformType::Float3:
		{
			const std::string& name = decl.Name;
			glm::vec3 value = *(glm::vec3*)(uniformBuffer.GetBuffer() + decl.Offset);

			UploadUniformVec3(name, value);
			break;
		}
		case UniformType::Float4:
		{
			const std::string& name = decl.Name;
			glm::vec4 value = *(glm::vec4*)(uniformBuffer.GetBuffer() + decl.Offset);

			UploadUniformVec4(name, value);
			break;
		}
		case UniformType::Matrix4x4:
		{
			const std::string& name = decl.Name;
			glm::mat4 value = *(glm::mat4*)(uniformBuffer.GetBuffer() + decl.Offset);

			UploadUniformMat4(name, value);
			break;
		}
		}
	}
}

std::string Kaiser::OpenGLShader::ReadFile(const std::string& path)
{
	std::ifstream stream(path, std::ios::in | std::ios::binary);

	std::string source;
	if (!stream)
	{
		KS_CORE_ERROR("Could not open file '{0}'", path);
	}
	else
	{
		stream.seekg(0, std::ios::end);
		source.resize(stream.tellg());
		stream.seekg(0, std::ios::beg);
		stream.read(&source[0], source.size());
		stream.close();
	}

	return source;

}

std::unordered_map<GLenum, std::string> Kaiser::OpenGLShader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> sources;
	
	const char* typeToken = "#type";
	size_t typeTokenLen = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		KS_CORE_ASSERT(eol != std::string::npos, "Syntax error");
		size_t begin = pos + typeTokenLen + 1;
		std::string type = source.substr(begin, eol - begin);
		KS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader Type Specified");
		
		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);
		sources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
	}
	
	return sources;
}

void Kaiser::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& sources)
{
	GLuint program = glCreateProgram();

	KS_CORE_ASSERT(sources.size() <= 2, "We only support 2 shaders for now");
	std::array<GLenum, (size_t)SupportedShaders::Max> shaderIds;
	int index = 0;
	
	for (auto& src : sources)
	{
		GLenum type = src.first;
		const std::string& sourceStr = src.second;

		GLuint shader = glCreateShader(type);

		const GLchar* source = sourceStr.c_str();
		glShaderSource(shader, 1, &source, 0);

		// Compile the shader
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);

			// Use the infoLog as you see fit.
			KS_CORE_ERROR("{0}", infoLog.data());
			KS_CORE_ASSERT(false, "Shader Compilation Failure!");

			// In this simple program, we'll just leave
			break;
		}
		
		glAttachShader(program, shader);
		shaderIds[index++] = shader;
	}
	
	mID = program;

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		for (auto id : shaderIds)
			glDeleteShader(id);

		KS_CORE_ERROR("{0}", infoLog.data());
		KS_CORE_ASSERT(false, "Shader link failure!");
		return;
	}

	for (auto id : shaderIds)
		glDetachShader(program, id);
	
}

void Kaiser::OpenGLShader::Bind() const
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		});
}

void Kaiser::OpenGLShader::Unbind() const
{
	Renderer::Submit([=] {
		glUseProgram(0);
		});
}

void Kaiser::OpenGLShader::UploadUniformVec4(const std::string& name, const glm::vec4& vector)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
		});
}

void Kaiser::OpenGLShader::UploadUniformInt(const std::string& name, const int& value)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		glUniform1i(location, value);
		});
}

void Kaiser::OpenGLShader::SetFloat(const std::string& name, float value)
{
	//Renderer::Submit([=]() {
		UploadUniformFloat(name, value);
		//});
}

void Kaiser::OpenGLShader::SetInt(const std::string& name, int value)
{
	//Renderer::Submit([=]() {
		UploadUniformInt(name, value);
		//});
}

void Kaiser::OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	//Renderer::Submit([=]() {
		UploadUniformMat4(name, value);
		//});
}



void Kaiser::OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		if (location == -1)
			KS_CORE_WARN("Uniform {0} not found!", name);
		glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
		});
}

void Kaiser::OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		if (location == -1)
			KS_CORE_WARN("Uniform {0} not found!", name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		});
}

void Kaiser::OpenGLShader::UploadUniformFloat(const std::string& name, const float& value)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		if (location == -1)
			KS_CORE_WARN("Uniform {0} not found!", name);
		glUniform1f(location, value);
		});
}

void Kaiser::OpenGLShader::UploadUniformVec2(const std::string& name, const glm::vec2& vector)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		if (location == -1)
			KS_CORE_WARN("Uniform {0} not found!", name);
		glUniform2f(location, vector.x, vector.y);
		});
}

void Kaiser::OpenGLShader::UploadUniformVec3(const std::string& name, const glm::vec3& vector)
{
	Renderer::Submit([=] {
		glUseProgram(mID);
		GLint location = glGetUniformLocation(mID, name.c_str());
		if (location == -1)
			KS_CORE_WARN("Uniform {0} not found!", name);
		glUniform3f(location, vector.x, vector.y, vector.z);
		});
}

GLenum Kaiser::ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	KS_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}
