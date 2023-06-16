#include "stdafx.h"
#include "WinInput.h"
#include <GLFW/glfw3.h>
#include "Kaiser/Application.h"



Kaiser::Input* Kaiser::Input::mInstance = new WinInput();

bool Kaiser::WinInput::IsKeyPressedImpl(int keycode)
{
	const auto& window = static_cast<GLFWwindow*>(Kaiser::Application::Get().GetWindow().GetNativeWindow());
	auto state = glfwGetKey(window, keycode);
	
	bool pressed = state == GLFW_PRESS || state == GLFW_REPEAT;
	
	return pressed;
	
	
}

bool Kaiser::WinInput::IsMouseButtonPressedImpl(int button)
{
	const auto& window = static_cast<GLFWwindow*>(Kaiser::Application::Get().GetWindow().GetNativeWindow());
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

glm::vec2 Kaiser::WinInput::GetMousePositionImpl()
{
	const auto& window = static_cast<GLFWwindow*>(Kaiser::Application::Get().GetWindow().GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
}

#include <glfw/glfw3.h>


Key KeyCode::Unknown(GLFW_KEY_UNKNOWN);

Key KeyCode::Space(GLFW_KEY_SPACE);
Key KeyCode::Apostrophe(GLFW_KEY_APOSTROPHE);
Key KeyCode::Comma(GLFW_KEY_COMMA);
Key KeyCode::Minus(GLFW_KEY_MINUS);
Key KeyCode::Period(GLFW_KEY_PERIOD);
Key KeyCode::Slash(GLFW_KEY_SLASH);
Key KeyCode::Zero(GLFW_KEY_0);
Key KeyCode::One(GLFW_KEY_1);
Key KeyCode::Two(GLFW_KEY_2);
Key KeyCode::Three(GLFW_KEY_3);
Key KeyCode::Four(GLFW_KEY_4);
Key KeyCode::Five(GLFW_KEY_5);
Key KeyCode::Six(GLFW_KEY_6);
Key KeyCode::Seven(GLFW_KEY_7);
Key KeyCode::Eight(GLFW_KEY_8);
Key KeyCode::Nine(GLFW_KEY_9);
Key KeyCode::Semicolon(GLFW_KEY_SEMICOLON);
Key KeyCode::Equal(GLFW_KEY_EQUAL);
Key KeyCode::A(GLFW_KEY_A);
Key KeyCode::B(GLFW_KEY_B);
Key KeyCode::C(GLFW_KEY_C);
Key KeyCode::D(GLFW_KEY_D);
Key KeyCode::E(GLFW_KEY_E);
Key KeyCode::F(GLFW_KEY_F);
Key KeyCode::G(GLFW_KEY_G);
Key KeyCode::H(GLFW_KEY_H);
Key KeyCode::I(GLFW_KEY_I);
Key KeyCode::J(GLFW_KEY_J);
Key KeyCode::K(GLFW_KEY_K);
Key KeyCode::L(GLFW_KEY_L);
Key KeyCode::M(GLFW_KEY_M);
Key KeyCode::N(GLFW_KEY_N);
Key KeyCode::O(GLFW_KEY_O);
Key KeyCode::P(GLFW_KEY_P);
Key KeyCode::Q(GLFW_KEY_Q);
Key KeyCode::R(GLFW_KEY_R);
Key KeyCode::S(GLFW_KEY_S);
Key KeyCode::T(GLFW_KEY_T);
Key KeyCode::U(GLFW_KEY_U);
Key KeyCode::V(GLFW_KEY_V);
Key KeyCode::W(GLFW_KEY_W);
Key KeyCode::X(GLFW_KEY_X);
Key KeyCode::Y(GLFW_KEY_Y);
Key KeyCode::Z(GLFW_KEY_Z);
Key KeyCode::LeftBracket(GLFW_KEY_LEFT_BRACKET);
Key KeyCode::Backslash(GLFW_KEY_BACKSLASH);
Key KeyCode::RightBracket(GLFW_KEY_RIGHT_BRACKET);
Key KeyCode::Grave(GLFW_KEY_GRAVE_ACCENT);
Key KeyCode::World1(GLFW_KEY_WORLD_1);
Key KeyCode::World2(GLFW_KEY_WORLD_2);

Key KeyCode::Escape(GLFW_KEY_ESCAPE);
Key KeyCode::Enter(GLFW_KEY_ENTER);
Key KeyCode::Tab(GLFW_KEY_TAB);
Key KeyCode::Backspace(GLFW_KEY_BACKSPACE);
Key KeyCode::Insert(GLFW_KEY_INSERT);
Key KeyCode::Delete(GLFW_KEY_DELETE);
Key KeyCode::Right(GLFW_KEY_RIGHT);
Key KeyCode::Left(GLFW_KEY_LEFT);
Key KeyCode::Down(GLFW_KEY_DOWN);
Key KeyCode::Up(GLFW_KEY_UP);
Key KeyCode::PageUp(GLFW_KEY_PAGE_UP);
Key KeyCode::PageDown(GLFW_KEY_PAGE_DOWN);
Key KeyCode::Home(GLFW_KEY_HOME);
Key KeyCode::End(GLFW_KEY_END);
Key KeyCode::CapsLock(GLFW_KEY_CAPS_LOCK);
Key KeyCode::ScrollLock(GLFW_KEY_SCROLL_LOCK);
Key KeyCode::NumLock(GLFW_KEY_NUM_LOCK);
Key KeyCode::PrintScreen(GLFW_KEY_PRINT_SCREEN);
Key KeyCode::Pause(GLFW_KEY_PAUSE);
Key KeyCode::F1(GLFW_KEY_F1);
Key KeyCode::F2(GLFW_KEY_F2);
Key KeyCode::F3(GLFW_KEY_F3);
Key KeyCode::F4(GLFW_KEY_F4);
Key KeyCode::F5(GLFW_KEY_F5);
Key KeyCode::F6(GLFW_KEY_F6);
Key KeyCode::F7(GLFW_KEY_F7);
Key KeyCode::F8(GLFW_KEY_F8);
Key KeyCode::F9(GLFW_KEY_F9);
Key KeyCode::F10(GLFW_KEY_F10);
Key KeyCode::F11(GLFW_KEY_F11);
Key KeyCode::F12(GLFW_KEY_F12);
Key KeyCode::F13(GLFW_KEY_F13);
Key KeyCode::F14(GLFW_KEY_F14);
Key KeyCode::F15(GLFW_KEY_F15);
Key KeyCode::F16(GLFW_KEY_F16);
Key KeyCode::F17(GLFW_KEY_F17);
Key KeyCode::F18(GLFW_KEY_F18);
Key KeyCode::F19(GLFW_KEY_F19);
Key KeyCode::F20(GLFW_KEY_F20);
Key KeyCode::F21(GLFW_KEY_F21);
Key KeyCode::F22(GLFW_KEY_F22);
Key KeyCode::F23(GLFW_KEY_F23);
Key KeyCode::F24(GLFW_KEY_F24);
Key KeyCode::F25(GLFW_KEY_F25);
Key KeyCode::KP0(GLFW_KEY_KP_0);
Key KeyCode::KP1(GLFW_KEY_KP_1);
Key KeyCode::KP2(GLFW_KEY_KP_2);
Key KeyCode::KP3(GLFW_KEY_KP_3);
Key KeyCode::KP4(GLFW_KEY_KP_4);
Key KeyCode::KP5(GLFW_KEY_KP_5);
Key KeyCode::KP6(GLFW_KEY_KP_6);
Key KeyCode::KP7(GLFW_KEY_KP_7);
Key KeyCode::KP8(GLFW_KEY_KP_8);
Key KeyCode::KP9(GLFW_KEY_KP_9);
Key KeyCode::KPDecimal(GLFW_KEY_KP_DECIMAL);
Key KeyCode::KPDivide(GLFW_KEY_KP_DIVIDE);
Key KeyCode::KPMultiply(GLFW_KEY_KP_MULTIPLY);
Key KeyCode::KPSubtract(GLFW_KEY_KP_SUBTRACT);
Key KeyCode::KPAdd(GLFW_KEY_KP_ADD);
Key KeyCode::KPEnter(GLFW_KEY_KP_ENTER);
Key KeyCode::KPEqual(GLFW_KEY_KP_EQUAL);
Key KeyCode::LeftShift(GLFW_KEY_LEFT_SHIFT);
Key KeyCode::LeftControl(GLFW_KEY_LEFT_CONTROL);
Key KeyCode::LeftAlt(GLFW_KEY_LEFT_ALT);
Key KeyCode::LeftSuper(GLFW_KEY_LEFT_SUPER);
Key KeyCode::RightShift(GLFW_KEY_RIGHT_SHIFT);
Key KeyCode::RightControl(GLFW_KEY_RIGHT_CONTROL);
Key KeyCode::RightAlt(GLFW_KEY_RIGHT_ALT);
Key KeyCode::RightSuper(GLFW_KEY_RIGHT_SUPER);
Key KeyCode::Menu(GLFW_KEY_MENU);

Key KeyCode::Last(GLFW_KEY_LAST);


std::string Key::ToString() const
{
	const char* keyName = glfwGetKeyName(m_KeyCode, 0);

	if (keyName)
		return std::string(keyName);
	else
		return std::string(" ");
}