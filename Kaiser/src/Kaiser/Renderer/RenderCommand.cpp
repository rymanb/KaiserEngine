#include "stdafx.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Kaiser
{
	Ref<RenderAPI> RenderCommand::sRenderAPI = CreateRef<OpenGLRenderAPI>();
}