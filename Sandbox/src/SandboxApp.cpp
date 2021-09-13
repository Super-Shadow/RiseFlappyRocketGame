#include <Rise.h>

class ExampleLayer : public Rise::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		RS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rise::Event& event) override
	{
		RS_TRACE("{0}", event);
	}

};

class Sandbox : public Rise::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() override
	{

	}
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}