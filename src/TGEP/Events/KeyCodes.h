#pragma once

#include "../pch.h"
#include "../ImGui/imgui.h"


namespace TGEP
{
	using KeyCode = uint16_t;
	
	namespace Key
	{
		enum : KeyCode
		{
			// From glfw3.h
			Space               = 32,
			Apostrophe          = 39, /* ' */
			Comma               = 44, /* , */
			Minus               = 45, /* - */
			Period              = 46, /* . */
			Slash               = 47, /* / */

			D0                  = 48, /* 0 */
			D1                  = 49, /* 1 */
			D2                  = 50, /* 2 */
			D3                  = 51, /* 3 */
			D4                  = 52, /* 4 */
			D5                  = 53, /* 5 */
			D6                  = 54, /* 6 */
			D7                  = 55, /* 7 */
			D8                  = 56, /* 8 */
			D9                  = 57, /* 9 */

			Semicolon           = 59, /* ; */
			Equal               = 61, /* = */

			A                   = 65,
			B                   = 66,
			C                   = 67,
			D                   = 68,
			E                   = 69,
			F                   = 70,
			G                   = 71,
			H                   = 72,
			I                   = 73,
			J                   = 74,
			K                   = 75,
			L                   = 76,
			M                   = 77,
			N                   = 78,
			O                   = 79,
			P                   = 80,
			Q                   = 81,
			R                   = 82,
			S                   = 83,
			T                   = 84,
			U                   = 85,
			V                   = 86,
			W                   = 87,
			X                   = 88,
			Y                   = 89,
			Z                   = 90,

			LeftBracket         = 91,  /* [ */
			Backslash           = 92,  /* \ */
			RightBracket        = 93,  /* ] */
			GraveAccent         = 96,  /* ` */

			World1              = 161, /* non-US #1 */
			World2              = 162, /* non-US #2 */

			/* Function keys */
			Escape              = 256,
			Enter               = 257,
			Tab                 = 258,
			Backspace           = 259,
			Insert              = 260,
			Delete              = 261,
			Right               = 262,
			Left                = 263,
			Down                = 264,
			Up                  = 265,
			PageUp              = 266,
			PageDown            = 267,
			Home                = 268,
			End                 = 269,
			CapsLock            = 280,
			ScrollLock          = 281,
			NumLock             = 282,
			PrintScreen         = 283,
			Pause               = 284,
			F1                  = 290,
			F2                  = 291,
			F3                  = 292,
			F4                  = 293,
			F5                  = 294,
			F6                  = 295,
			F7                  = 296,
			F8                  = 297,
			F9                  = 298,
			F10                 = 299,
			F11                 = 300,
			F12                 = 301,
			F13                 = 302,
			F14                 = 303,
			F15                 = 304,
			F16                 = 305,
			F17                 = 306,
			F18                 = 307,
			F19                 = 308,
			F20                 = 309,
			F21                 = 310,
			F22                 = 311,
			F23                 = 312,
			F24                 = 313,
			F25                 = 314,

			/* Keypad */
			KP0                 = 320,
			KP1                 = 321,
			KP2                 = 322,
			KP3                 = 323,
			KP4                 = 324,
			KP5                 = 325,
			KP6                 = 326,
			KP7                 = 327,
			KP8                 = 328,
			KP9                 = 329,
			KPDecimal           = 330,
			KPDivide            = 331,
			KPMultiply          = 332,
			KPSubtract          = 333,
			KPAdd               = 334,
			KPEnter             = 335,
			KPEqual             = 336,

			LeftShift           = 340,
			LeftControl         = 341,
			LeftAlt             = 342,
			LeftSuper           = 343,
			RightShift          = 344,
			RightControl        = 345,
			RightAlt            = 346,
			RightSuper          = 347,
			Menu                = 348
		};
	}

	static ImGuiKey TGEPKeycodeToImGuiKeycode(int key)
	{
		switch (key)
		{
			case TGEP::Key::Tab: return ImGuiKey_Tab;
			case TGEP::Key::Delete: return ImGuiKey_Delete;
			case TGEP::Key::Backspace: return ImGuiKey_Backspace;
			case TGEP::Key::Space: return ImGuiKey_Space;
			case TGEP::Key::Enter: return ImGuiKey_Enter;
			case TGEP::Key::Escape: return ImGuiKey_Escape;
			case TGEP::Key::Apostrophe: return ImGuiKey_Apostrophe;
			case TGEP::Key::Comma: return ImGuiKey_Comma;
			case TGEP::Key::Minus: return ImGuiKey_Minus;
			case TGEP::Key::Period: return ImGuiKey_Period;
			case TGEP::Key::Slash: return ImGuiKey_Slash;
			case TGEP::Key::Semicolon: return ImGuiKey_Semicolon;
			case TGEP::Key::Equal: return ImGuiKey_Equal;
			case TGEP::Key::LeftBracket: return ImGuiKey_LeftBracket;
			case TGEP::Key::Backslash: return ImGuiKey_Backslash;
			case TGEP::Key::RightBracket: return ImGuiKey_RightBracket;
			case TGEP::Key::LeftShift: return ImGuiKey_LeftShift;
			case TGEP::Key::LeftControl: return ImGuiKey_LeftCtrl;
			case TGEP::Key::LeftAlt: return ImGuiKey_LeftAlt;
			case TGEP::Key::Menu: return ImGuiKey_Menu;
			case TGEP::Key::D0: return ImGuiKey_0;
			case TGEP::Key::D1: return ImGuiKey_1;
			case TGEP::Key::D2: return ImGuiKey_2;
			case TGEP::Key::D3: return ImGuiKey_3;
			case TGEP::Key::D4: return ImGuiKey_4;
			case TGEP::Key::D5: return ImGuiKey_5;
			case TGEP::Key::D6: return ImGuiKey_6;
			case TGEP::Key::D7: return ImGuiKey_7;
			case TGEP::Key::D8: return ImGuiKey_8;
			case TGEP::Key::D9: return ImGuiKey_9;
			case TGEP::Key::A: return ImGuiKey_A;
			case TGEP::Key::B: return ImGuiKey_B;
			case TGEP::Key::C: return ImGuiKey_C;
			case TGEP::Key::D: return ImGuiKey_D;
			case TGEP::Key::E: return ImGuiKey_E;
			case TGEP::Key::F: return ImGuiKey_F;
			case TGEP::Key::G: return ImGuiKey_G;
			case TGEP::Key::H: return ImGuiKey_H;
			case TGEP::Key::I: return ImGuiKey_I;
			case TGEP::Key::J: return ImGuiKey_J;
			case TGEP::Key::K: return ImGuiKey_K;
			case TGEP::Key::L: return ImGuiKey_L;
			case TGEP::Key::M: return ImGuiKey_M;
			case TGEP::Key::N: return ImGuiKey_N;
			case TGEP::Key::O: return ImGuiKey_O;
			case TGEP::Key::P: return ImGuiKey_P;
			case TGEP::Key::Q: return ImGuiKey_Q;
			case TGEP::Key::R: return ImGuiKey_R;
			case TGEP::Key::S: return ImGuiKey_S;
			case TGEP::Key::T: return ImGuiKey_T;
			case TGEP::Key::U: return ImGuiKey_U;
			case TGEP::Key::V: return ImGuiKey_V;
			case TGEP::Key::W: return ImGuiKey_W;
			case TGEP::Key::X: return ImGuiKey_X;
			case TGEP::Key::Y: return ImGuiKey_Y;
			case TGEP::Key::Z: return ImGuiKey_Z;
			case TGEP::Key::F1: return ImGuiKey_F1;
			case TGEP::Key::F2: return ImGuiKey_F2;
			case TGEP::Key::F3: return ImGuiKey_F3;
			case TGEP::Key::F4: return ImGuiKey_F4;
			case TGEP::Key::F5: return ImGuiKey_F5;
			case TGEP::Key::F6: return ImGuiKey_F6;
			case TGEP::Key::F7: return ImGuiKey_F7;
			case TGEP::Key::F8: return ImGuiKey_F8;
			case TGEP::Key::F9: return ImGuiKey_F9;
			case TGEP::Key::F10: return ImGuiKey_F10;
			case TGEP::Key::F11: return ImGuiKey_F11;
			case TGEP::Key::F12: return ImGuiKey_F12;
			default: return ImGuiKey_None;
		}
	}
}