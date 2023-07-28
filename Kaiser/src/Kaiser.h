#pragma once

#pragma comment(lib, "dwmapi.lib")

#include "Kaiser/Core/Application.h"
#include "Kaiser/Core/Trace.h"
#include "Kaiser/Core/CrashDump.h"
#include "Kaiser/Core/Layer.h"
#include "Kaiser/Core/Input.h"
#include "Kaiser/Core/Keycode.h"

#include "Kaiser/ImGui/ImGuiLayer.h"

// events
#include "Kaiser/Core/Events/Event.h"
#include "Kaiser/Core/Events/AppEvent.h"
#include "Kaiser/Core/Events/KeyEvent.h"
#include "Kaiser/Core/Events/MouseEvent.h"

#include "Kaiser/Memory/MemoryManager.h"

#include "Kaiser/Renderer/Renderer.h"

#include "Kaiser/Renderer/Buffer.h"
#include "Kaiser/Renderer/VertexArray.h"
#include "Kaiser/Renderer/Shader.h"

#include "Kaiser/Renderer/Camera.h"

#include "Kaiser/Core/Engine.h"
#include "Kaiser/Scene/SceneManager.h"
#include "Kaiser/Scene/Scene.h"

#include "Kaiser/Entity/UUID.h"
#include "Kaiser/Entity/ECS.h"
#include "Kaiser/Entity/Entity.h"

#include "Kaiser/Entity/Component.h"
#include "Kaiser/Entity/ComponentFactory.h"

#include "Kaiser/Core/Time.h"

#include "Kaiser/Renderer/Texture.h"
#include "Kaiser/Renderer/Framebuffer.h"
#include "Kaiser/Renderer/Material.h"
// ---Entry Point---------------------
#include "Kaiser/EntryPoint.h"
// -----------------------------------
