#include <Rise.h>

class Sandbox : public Rise::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox() override
	{

	}
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}