#include "rspch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

#ifdef HZ_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Rise
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef RS_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			RS_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}