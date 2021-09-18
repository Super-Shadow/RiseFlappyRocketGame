#pragma once

#include "Core.h"

#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Rise
{
	class RISE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		[[nodiscard]] Window& GetWindow() const { return *m_Window; }
		[[nodiscard]] static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		static Application* s_Instance;
	};

	// Define in client
	Application* CreateApplication();
}
