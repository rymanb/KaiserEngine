#include "stdafx.h"
#include "Shader.h"

#include <glad/glad.h>

#include "Kaiser/Trace.h"

Kaiser::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	// Read our shaders into the appropriate buffers
	//std::string& vertexSource = vertexSrc;// Get source code for vertex shader.
	//std::string& fragmentSource = fragmentSrc;// Get source code for fragment shader.

		// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		KS_CORE_ERROR("{0}", infoLog.data());
		KS_CORE_ASSERT(false, "Vertex Shader Compilation Failure!");

		// In this simple program, we'll just leave
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		KS_CORE_ERROR("{0}", infoLog.data());
		KS_CORE_ASSERT(false, "Fragment Shader Compilation Failure!");
		

		// In this simple program, we'll just leave
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	shaderID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	// Link our program
	glLinkProgram(shaderID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(shaderID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(shaderID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.
		KS_CORE_ERROR("{0}", infoLog.data());
		KS_CORE_ASSERT(false, "Shader Link Failure!");

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(shaderID, vertexShader);
	glDetachShader(shaderID, fragmentShader);
}

Kaiser::Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

void Kaiser::Shader::Bind() const
{
	glUseProgram(shaderID);
}

void Kaiser::Shader::Unbind() const
{
	glUseProgram(0);
}
