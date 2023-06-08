#pragma once

#include "Kaiser/Core.h"
#include "Kaiser/Events/Event.h"
#include "Kaiser/Input.h"


namespace Kaiser
{
	class WinInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual glm::vec2 GetMousePositionImpl() override;
		//virtual float GetMouseXImpl() override;
		//virtual float GetMouseYImpl() override;
	};
}

