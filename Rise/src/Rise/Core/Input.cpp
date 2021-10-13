#include "rspch.h"

#ifdef RS_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Rise
{

	Scope<Input> Input::s_Instance = Create();

	Scope<Input> Input::Create()
	{
		#ifdef RS_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			RS_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}