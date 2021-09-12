#pragma once

#ifdef RS_PLATFORM_WINDOWS

extern Rise::Application* Rise::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Rise::CreateApplication();
	app->Run();
	delete app;
}

#endif
