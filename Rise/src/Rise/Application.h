#pragma once

#include "Core.h"

namespace Rise
{
	class RISE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Define in client
	Application* CreateApplication();
}
