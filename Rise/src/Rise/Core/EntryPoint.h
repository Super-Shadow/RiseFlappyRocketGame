#pragma once

#ifdef RS_PLATFORM_WINDOWS

inline int main(int argc, char** argv)
{
	Rise::Log::Init();
	RS_CORE_WARN("Initialised Log!");
	auto a = 5;
	RS_INFO("Hello! Var={0}", a);

	const auto app = Rise::CreateApplication();
	app->Run();
	delete app;
}

#endif
