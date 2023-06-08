#pragma once

#include "Kaiser/Core.h"
#include "Keycode.h"

namespace Kaiser
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0; 
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual glm::vec2 GetMousePositionImpl() = 0;
		
	private:
		static Input* s_Instance;
	};
}