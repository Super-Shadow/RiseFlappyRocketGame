#include <Rise.h>
// --Entry Point-------------
#include <Rise/Core/EntryPoint.h>
// --------------------------

#include "GameLayer.h"

class Sandbox final : public Rise::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new GameLayer());
	}

	Sandbox(const Sandbox&) = delete;
	Sandbox& operator=(const Sandbox&) = delete;

	Sandbox(Sandbox&&) = delete;
	Sandbox& operator=(Sandbox&&) = delete;

	~Sandbox() override = default;
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}