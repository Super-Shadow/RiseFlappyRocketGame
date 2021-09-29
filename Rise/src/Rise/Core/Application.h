#pragma once

#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Rise/Events/ApplicationEvent.h"
#include "Rise/ImGui/ImGuiLayer.h"

namespace Rise
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		[[nodiscard]] Window& GetWindow() const { return *m_Window; }
		[[nodiscard]] static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(const WindowCloseEvent& e);
		bool OnWindowResize(const WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_UpdateBuffers = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;


		static Application* s_Instance;
	};

	// Define in client
	Application* CreateApplication();
}
