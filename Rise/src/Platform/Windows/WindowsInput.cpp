#include "rspch.h"
#include "WindowsInput.h"

#include "Rise/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Rise
{
	bool WindowsInput::IsKeyPressedImpl(const KeyCode keyCode)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const auto state = glfwGetKey(window, static_cast<int>(keyCode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const MouseCode button)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float WindowsInput::GetMouseXImpl()
	{
		const auto [x, y] = WindowsInput::GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		const auto [x, y] = WindowsInput::GetMousePositionImpl();
		return y;
	}
}
