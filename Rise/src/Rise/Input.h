#pragma once

#include "Rise/Core.h"

namespace Rise
{
	class RISE_API Input
	{
	public:
		static bool IsKeyPressed(const int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) abstract;

		virtual bool IsMouseButtonPressedImpl(int button) abstract;
		virtual std::pair<float, float> GetMousePositionImpl() abstract;
		virtual float GetMouseXImpl() abstract;
		virtual float GetMouseYImpl() abstract;
	private:
		static Input* s_Instance;
	};
}