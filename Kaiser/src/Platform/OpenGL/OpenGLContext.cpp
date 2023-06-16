#include "stdafx.h"
#include "OpenGLContext.h"

#include "Kaiser/Trace.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>

Kaiser::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
{
	KS_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void Kaiser::OpenGLContext::Init()
{
	glfwMakeContextCurrent(mWindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	KS_CORE_ASSERT(status, "Failed to initialize Glad!");

	auto version = glGetString(GL_VERSION);

	
	KS_CORE_INFO("OpenGL Info:");
	KS_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
	KS_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
	KS_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));
	
}

void Kaiser::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(mWindowHandle);
}
