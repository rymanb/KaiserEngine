#include "stdafx.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

static void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		KS_CORE_ERROR("{0}", message);
		KS_CORE_ASSERT(false, "");
	}
	else
	{
		// HZ_CORE_TRACE("{0}", message);
	}
}

void Kaiser::OpenGLRenderAPI::Init()
{

	glDebugMessageCallback(OpenGLLogMessage, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto& caps = RenderAPI::GetCapabilities();

	caps.Vendor = (const char*)glGetString(GL_VENDOR);
	caps.Renderer = (const char*)glGetString(GL_RENDERER);
	caps.Version = (const char*)glGetString(GL_VERSION);

	glGetIntegerv(GL_MAX_SAMPLES, &caps.MaxSamples);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &caps.MaxAnisotropy);

	GLenum error = glGetError();
	while (error != GL_NO_ERROR)
	{
		KS_CORE_ERROR("OpenGL Error {0}", error);
		error = glGetError();
	}
}

void Kaiser::OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Kaiser::OpenGLRenderAPI::Clear()
{
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Kaiser::OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Kaiser::OpenGLRenderAPI::DrawIndexed(uint32_t count, bool depthTest)
{
	if (depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
