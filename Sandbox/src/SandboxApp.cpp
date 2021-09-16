#include <Rise.h>

class ExampleLayer : public Rise::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if(Rise::Input::IsKeyPressed(RS_KEY_TAB))
		{
			RS_TRACE("Tab key is pressed! (poll)");
		}
	}

	void OnEvent(Rise::Event& event) override
	{
		//RS_TRACE("{0}", event);

		if(event.GetEventType() == Rise::EventType::KeyPressed)
		{
			RS_TRACE("Tab key is pressed! (event)");

			const auto& e = dynamic_cast<Rise::KeyPressedEvent&>(event);
			RS_CORE_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
		}
	}

};

class Sandbox : public Rise::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Rise::ImGuiLayer());
	}

	~Sandbox() override
	{

	}
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}