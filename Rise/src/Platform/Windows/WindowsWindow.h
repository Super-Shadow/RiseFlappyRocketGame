#pragma once

#include "Rise/Window.h"
#include "Rise/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Rise
{
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		[[nodiscard]] unsigned int GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override;

		[[nodiscard]] void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			int Width = 1280, Height = 720;
			bool VSync = true;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}



