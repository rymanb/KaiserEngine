#include "stdafx.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Kaiser
{
	RenderAPI* RenderCommand::sRenderAPI = new OpenGLRenderAPI;
}