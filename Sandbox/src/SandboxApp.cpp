#include <Rise.h>

#include "imgui/imgui.h"

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

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
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
	}

	~Sandbox() override
	{

	}
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}