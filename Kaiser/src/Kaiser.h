#pragma once

#pragma comment(lib, "dwmapi.lib")

#include "Kaiser/Application.h"
#include "Kaiser/Trace.h"
#include "Kaiser/CrashDump.h"
#include "Kaiser/Layer.h"
#include "Kaiser/Input.h"
#include "Kaiser/Keycode.h"

#include "Kaiser/ImGui/ImGuiLayer.h"

// events
#include "Kaiser/Events/Event.h"
#include "Kaiser/Events/AppEvent.h"
#include "Kaiser/Events/KeyEvent.h"
#include "Kaiser/Events/MouseEvent.h"

#include "Kaiser/Memory/MemoryManager.h"

#include "Kaiser/Renderer/Renderer.h"

#include "Kaiser/Renderer/Buffer.h"
#include "Kaiser/Renderer/VertexArray.h"
#include "Kaiser/Renderer/Shader.h"

#include "Kaiser/Renderer/Camera.h"

#include "Kaiser/Engine.h"
#include "Kaiser/SceneManager.h"
#include "Kaiser/Scene.h"

#include "Kaiser/UUID.h"
#include "Kaiser/ECS.h"
#include "Kaiser/Entity.h"

#include "Kaiser/Component.h"
// ---Entry Point---------------------
#include "Kaiser/EntryPoint.h"
// -----------------------------------
