#pragma once

#include "Rise/Core/Core.h"

namespace Rise
{
	class RISE_API Input
	{
	public:
		// Delete these to make this class pure singleton
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(const int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		~Input() = default;
		Input() = default;

		virtual bool IsKeyPressedImpl(int keyCode) abstract;

		virtual bool IsMouseButtonPressedImpl(int button) abstract;
		virtual std::pair<float, float> GetMousePositionImpl() abstract;
		virtual float GetMouseXImpl() abstract;
		virtual float GetMouseYImpl() abstract;
	private:
		static Scope<Input> s_Instance;
	};
}