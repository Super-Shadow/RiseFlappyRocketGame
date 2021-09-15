#pragma once

#include "Rise/Layer.h"

#include "Rise/Events/MouseEvent.h"
#include "Rise/Events/ApplicationEvent.h"
#include "Rise/Events/KeyEvent.h"

namespace Rise
{
	class RISE_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& e);
		bool OnOnMouseMovedEvent(const MouseMovedEvent& e);
		bool OnMouseScrolledEvent(const MouseScrolledEvent& e);
		bool OnKeyPressedEvent(const KeyPressedEvent& e);
		bool OnKeyReleasedEvent(const KeyReleasedEvent& e);
		bool OnKeyTypedEvent(const KeyTypedEvent& e);
		bool OnWindowResizedEvent(const WindowResizeEvent& e);

		float m_Time = 0.0f;
	};
}
