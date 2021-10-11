#pragma once

#include <utility>

#include "rspch.h"

#include "Rise/Core/Core.h"
#include "Rise/Events/Event.h"

namespace Rise
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string title = "Rise Engine", const unsigned int width = 1280, const unsigned int height = 720) : Title(std::move(title)), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based Window

	class RISE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(const Window&) = delete;
		Window& operator= (const Window&) = delete;

		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		virtual ~Window() = default;

		virtual void OnUpdate() abstract;

		[[nodiscard]] virtual unsigned int GetWidth() const abstract;
		[[nodiscard]] virtual unsigned int GetHeight() const abstract;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) abstract;
		virtual void SetVSync(bool enabled) abstract;
		[[nodiscard]] virtual bool IsVSync() const abstract;

		[[nodiscard]] virtual void* GetNativeWindow() const abstract;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	protected:
		Window() = default;
	};
}
