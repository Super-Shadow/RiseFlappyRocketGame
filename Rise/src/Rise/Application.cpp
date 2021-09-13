#include "Application.h"

#include "Rise/Log.h"
#include "Rise/Events/ApplicationEvent.h"

namespace Rise
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if(e.IsInCategory(EventCategoryInput))
			RS_TRACE(e);

		while (true)
		{
			
		}
	}
}
