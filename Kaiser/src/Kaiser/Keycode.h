#pragma once

#include "stdafx.h"
#include "Kaiser/Core.h"




class Key
{
public:
	Key(int key) : m_KeyCode(key) {}
	std::string ToString() const;
	
	operator int() const { return m_KeyCode; }
	
	operator bool() const { return m_KeyCode != -1; }
	
	bool operator==(Key other) const
	{
		return m_KeyCode == other.m_KeyCode;
	}

	bool operator!=(Key other) const
	{
		return !(*this == other);
	}

	operator std::string() const { return ToString(); }
	

	operator const char() const 
	{ 
		const auto& str = ToString();
		return str.empty() ? '\0' : str[0];
	}

	

private:
	int m_KeyCode;	
};

class KeyCode
{
public:

	// make it so you can do KeyCode.A as well as KeyCode::A
	
	static Key Get(int key) { return Key(key); }

	
	// From glfw3.h
	
	/* The unknown key */
	static Key Unknown;
	
	/* Printable keys */
	static Key Space;
	static Key Apostrophe;
	static Key Comma;
	static Key Minus;
	static Key Period;
	static Key Slash;
	static Key Zero; ;
	static Key One;
	static Key Two; ;
	static Key Three; ;
	static Key Four; ;
	static Key Five; ;
	static Key Six;
	static Key Seven; ;
	static Key Eight; ;
	static Key Nine; ;
	static Key Semicolon;
	static Key Equal;
	static Key A;
	static Key B;
	static Key C;
	static Key D;
	static Key E;
	static Key F;
	static Key G;
	static Key H;
	static Key I;
	static Key J;
	static Key K;
	static Key L;
	static Key M;
	static Key N;
	static Key O;
	static Key P;
	static Key Q;
	static Key R;
	static Key S;
	static Key T;
	static Key U;
	static Key V;
	static Key W;
	static Key X;
	static Key Y;
	static Key Z;
	static Key LeftBracket;
	static Key Backslash;
	static Key RightBracket;
	static Key Grave;
	static Key World1;
	static Key World2;
	
	/* Function keys */
	static Key Escape;
	static Key Enter;
	static Key Tab;
	static Key Backspace;
	static Key Insert;
	static Key Delete;
	static Key Right;
	static Key Left;
	static Key Down;
	static Key Up;
	static Key PageUp;
	static Key PageDown;
	static Key Home;
	static Key End;
	static Key CapsLock;
	static Key ScrollLock;
	static Key NumLock;
	static Key PrintScreen;
	static Key Pause;
	static Key F1;
	static Key F2;
	static Key F3;
	static Key F4;
	static Key F5;
	static Key F6;
	static Key F7;
	static Key F8;
	static Key F9;
	static Key F10;
	static Key F11;
	static Key F12;
	static Key F13;
	static Key F14;
	static Key F15;
	static Key F16;
	static Key F17;
	static Key F18;
	static Key F19;
	static Key F20;
	static Key F21;
	static Key F22;
	static Key F23;
	static Key F24;
	static Key F25;
	static Key KP0;
	static Key KP1;
	static Key KP2;
	static Key KP3;
	static Key KP4;
	static Key KP5;
	static Key KP6;
	static Key KP7;
	static Key KP8;
	static Key KP9;
	static Key KPDecimal;
	static Key KPDivide;
	static Key KPMultiply;
	static Key KPSubtract;
	static Key KPAdd;
	static Key KPEnter;
	static Key KPEqual;
	static Key LeftShift;
	static Key LeftControl;
	static Key LeftAlt;
	static Key LeftSuper;
	static Key RightShift;
	static Key RightControl;
	static Key RightAlt;
	static Key RightSuper;
	static Key Menu;
	
	static Key Last;


	
	
};