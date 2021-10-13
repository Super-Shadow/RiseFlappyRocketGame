#pragma once

#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Rise/Events/ApplicationEvent.h"
#include "Rise/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Rise
{
	class Application
	{
	public:
		Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		[[nodiscard]] Window& GetWindow() const { return *m_Window; }
		[[nodiscard]] static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClosed(const WindowCloseEvent& e);
		bool OnWindowResize(const WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_UpdateBuffers = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		friend int ::main(int argc, char** argv); // TODO: I don't like this neither does resharper. See entrypoint.h
		static Application* s_Instance;
	};

	// Define in client
	Application* CreateApplication();
}
