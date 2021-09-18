#include "rspch.h"

#include "Application.h"
#include <glad/glad.h>

namespace Rise
{
//#define BIND_EVENT_FN(x) [this]<typename T0>(T0&& PH1) { Application::x(std::forward<T0>(PH1)); }

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		RS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RS_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Setup arrays and buffers

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);


		// Plot our triange on X Y Z coordinates. X is horizontal and Y is vertical and Z is depth. X is -1 to 1 and Y is -1 bottom and 1 top.
		constexpr float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// Pass our triangle into buffer. Static draw since it wont change at runtime.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Tell openGL that the bytes just passed in are 3 vec3's
		glEnableVertexAttribArray(0); // Enable index 0 (first param of next line) of our attrib data
		
		// First param is the index, next two params are telling it that the bytes are 3 floats. Next param is telling it that they are not normalised.
		// Next param is the amount of bytes between the vertices (So the space for each verticie aka 3(each point for triangle) * 4(size of a float).
		// Last param is the offset for this specific attribute when it is applied to our vertices data thing. We want it to start at the beginning of each vec3 coordinate.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		constexpr uint32_t indices[3] = {0, 1, 2};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

		const std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		const std::string pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;

			void main()
			{
				//colour = vec4(0.8, 0.2, 0.3, 1.0);
				colour = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";


		m_Shader.reset(new Shader(vertexSrc, pixelSrc));

	}


	Application::~Application()
	{
	}


	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			// Draws our triangle
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); // Can pass nullptr for indices as they are tied to the same glGenBuffers(1, ...) so it just is automatically linked.

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RS_BIND_EVENT_FN(Application::OnWindowClosed));

		//RS_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
