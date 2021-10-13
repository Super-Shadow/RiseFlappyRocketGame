#pragma once

#include "Rise/Core/Input.h"

namespace Rise
{
	class WindowsInput final : public Input
	{
	protected:
		bool IsKeyPressedImpl(KeyCode keyCode) override;

		bool IsMouseButtonPressedImpl(MouseCode button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}
