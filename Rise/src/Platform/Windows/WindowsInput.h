#pragma once

#include "Rise/Input.h"

namespace Rise
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keyCode) override;

		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}
