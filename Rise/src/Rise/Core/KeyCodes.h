#pragma once

namespace Rise
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys from glfw3.h */
#define RS_KEY_SPACE           ::Rise::Key::Space
#define RS_KEY_APOSTROPHE      ::Rise::Key::Apostrophe    /* ' */
#define RS_KEY_COMMA           ::Rise::Key::Comma         /* , */
#define RS_KEY_MINUS           ::Rise::Key::Minus         /* - */
#define RS_KEY_PERIOD          ::Rise::Key::Period        /* . */
#define RS_KEY_SLASH           ::Rise::Key::Slash         /* / */
#define RS_KEY_0               ::Rise::Key::D0
#define RS_KEY_1               ::Rise::Key::D1
#define RS_KEY_2               ::Rise::Key::D2
#define RS_KEY_3               ::Rise::Key::D3
#define RS_KEY_4               ::Rise::Key::D4
#define RS_KEY_5               ::Rise::Key::D5
#define RS_KEY_6               ::Rise::Key::D6
#define RS_KEY_7               ::Rise::Key::D7
#define RS_KEY_8               ::Rise::Key::D8
#define RS_KEY_9               ::Rise::Key::D9
#define RS_KEY_SEMICOLON       ::Rise::Key::Semicolon     /* ; */
#define RS_KEY_EQUAL           ::Rise::Key::Equal         /* = */
#define RS_KEY_A               ::Rise::Key::A
#define RS_KEY_B               ::Rise::Key::B
#define RS_KEY_C               ::Rise::Key::C
#define RS_KEY_D               ::Rise::Key::D
#define RS_KEY_E               ::Rise::Key::E
#define RS_KEY_F               ::Rise::Key::F
#define RS_KEY_G               ::Rise::Key::G
#define RS_KEY_H               ::Rise::Key::H
#define RS_KEY_I               ::Rise::Key::I
#define RS_KEY_J               ::Rise::Key::J
#define RS_KEY_K               ::Rise::Key::K
#define RS_KEY_L               ::Rise::Key::L
#define RS_KEY_M               ::Rise::Key::M
#define RS_KEY_N               ::Rise::Key::N
#define RS_KEY_O               ::Rise::Key::O
#define RS_KEY_P               ::Rise::Key::P
#define RS_KEY_Q               ::Rise::Key::Q
#define RS_KEY_R               ::Rise::Key::R
#define RS_KEY_S               ::Rise::Key::S
#define RS_KEY_T               ::Rise::Key::T
#define RS_KEY_U               ::Rise::Key::U
#define RS_KEY_V               ::Rise::Key::V
#define RS_KEY_W               ::Rise::Key::W
#define RS_KEY_X               ::Rise::Key::X
#define RS_KEY_Y               ::Rise::Key::Y
#define RS_KEY_Z               ::Rise::Key::Z
#define RS_KEY_LEFT_BRACKET    ::Rise::Key::LeftBracket   /* [ */
#define RS_KEY_BACKSLASH       ::Rise::Key::Backslash     /* \ */
#define RS_KEY_RIGHT_BRACKET   ::Rise::Key::RightBracket  /* ] */
#define RS_KEY_GRAVE_ACCENT    ::Rise::Key::GraveAccent   /* ` */
#define RS_KEY_WORLD_1         ::Rise::Key::World1        /* non-US #1 */
#define RS_KEY_WORLD_2         ::Rise::Key::World2        /* non-US #2 */

/* Function keys */
#define RS_KEY_ESCAPE          ::Rise::Key::Escape
#define RS_KEY_ENTER           ::Rise::Key::Enter
#define RS_KEY_TAB             ::Rise::Key::Tab
#define RS_KEY_BACKSPACE       ::Rise::Key::Backspace
#define RS_KEY_INSERT          ::Rise::Key::Insert
#define RS_KEY_DELETE          ::Rise::Key::Delete
#define RS_KEY_RIGHT           ::Rise::Key::Right
#define RS_KEY_LEFT            ::Rise::Key::Left
#define RS_KEY_DOWN            ::Rise::Key::Down
#define RS_KEY_UP              ::Rise::Key::Up
#define RS_KEY_PAGE_UP         ::Rise::Key::PageUp
#define RS_KEY_PAGE_DOWN       ::Rise::Key::PageDown
#define RS_KEY_HOME            ::Rise::Key::Home
#define RS_KEY_END             ::Rise::Key::End
#define RS_KEY_CAPS_LOCK       ::Rise::Key::CapsLock
#define RS_KEY_SCROLL_LOCK     ::Rise::Key::ScrollLock
#define RS_KEY_NUM_LOCK        ::Rise::Key::NumLock
#define RS_KEY_PRINT_SCREEN    ::Rise::Key::PrintScreen
#define RS_KEY_PAUSE           ::Rise::Key::Pause
#define RS_KEY_F1              ::Rise::Key::F1
#define RS_KEY_F2              ::Rise::Key::F2
#define RS_KEY_F3              ::Rise::Key::F3
#define RS_KEY_F4              ::Rise::Key::F4
#define RS_KEY_F5              ::Rise::Key::F5
#define RS_KEY_F6              ::Rise::Key::F6
#define RS_KEY_F7              ::Rise::Key::F7
#define RS_KEY_F8              ::Rise::Key::F8
#define RS_KEY_F9              ::Rise::Key::F9
#define RS_KEY_F10             ::Rise::Key::F10
#define RS_KEY_F11             ::Rise::Key::F11
#define RS_KEY_F12             ::Rise::Key::F12
#define RS_KEY_F13             ::Rise::Key::F13
#define RS_KEY_F14             ::Rise::Key::F14
#define RS_KEY_F15             ::Rise::Key::F15
#define RS_KEY_F16             ::Rise::Key::F16
#define RS_KEY_F17             ::Rise::Key::F17
#define RS_KEY_F18             ::Rise::Key::F18
#define RS_KEY_F19             ::Rise::Key::F19
#define RS_KEY_F20             ::Rise::Key::F20
#define RS_KEY_F21             ::Rise::Key::F21
#define RS_KEY_F22             ::Rise::Key::F22
#define RS_KEY_F23             ::Rise::Key::F23
#define RS_KEY_F24             ::Rise::Key::F24
#define RS_KEY_F25             ::Rise::Key::F25

/* Keypad */
#define RS_KEY_KP_0            ::Rise::Key::KP0
#define RS_KEY_KP_1            ::Rise::Key::KP1
#define RS_KEY_KP_2            ::Rise::Key::KP2
#define RS_KEY_KP_3            ::Rise::Key::KP3
#define RS_KEY_KP_4            ::Rise::Key::KP4
#define RS_KEY_KP_5            ::Rise::Key::KP5
#define RS_KEY_KP_6            ::Rise::Key::KP6
#define RS_KEY_KP_7            ::Rise::Key::KP7
#define RS_KEY_KP_8            ::Rise::Key::KP8
#define RS_KEY_KP_9            ::Rise::Key::KP9
#define RS_KEY_KP_DECIMAL      ::Rise::Key::KPDecimal
#define RS_KEY_KP_DIVIDE       ::Rise::Key::KPDivide
#define RS_KEY_KP_MULTIPLY     ::Rise::Key::KPMultiply
#define RS_KEY_KP_SUBTRACT     ::Rise::Key::KPSubtract
#define RS_KEY_KP_ADD          ::Rise::Key::KPAdd
#define RS_KEY_KP_ENTER        ::Rise::Key::KPEnter
#define RS_KEY_KP_EQUAL        ::Rise::Key::KPEqual

#define RS_KEY_LEFT_SHIFT      ::Rise::Key::LeftShift
#define RS_KEY_LEFT_CONTROL    ::Rise::Key::LeftControl
#define RS_KEY_LEFT_ALT        ::Rise::Key::LeftAlt
#define RS_KEY_LEFT_SUPER      ::Rise::Key::LeftSuper
#define RS_KEY_RIGHT_SHIFT     ::Rise::Key::RightShift
#define RS_KEY_RIGHT_CONTROL   ::Rise::Key::RightControl
#define RS_KEY_RIGHT_ALT       ::Rise::Key::RightAlt
#define RS_KEY_RIGHT_SUPER     ::Rise::Key::RightSuper
#define RS_KEY_MENU            ::Rise::Key::Menu