#include "rspch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

namespace Rise
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		RS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RS_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		// Plot our triange on X Y Z coordinates. X is horizontal and Y is vertical and Z is depth. X is -1 to 1 and Y is -1 bottom and 1 top.
		constexpr float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof vertices));

		const BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		constexpr uint32_t indices[3] = {0, 1, 2};
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, static_cast<uint32_t>(std::size(indices))));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());

		constexpr float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,	 0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, static_cast<uint32_t>(sizeof squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		constexpr uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, static_cast<uint32_t>(std::size(squareIndices))));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		const std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		const std::string pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			in vec4 v_Colour;

			void main()
			{
				//colour = vec4(0.8, 0.2, 0.3, 1.0);
				colour = vec4(v_Position * 0.5 + 0.5, 1.0);
				colour = v_Colour;
			}
		)";
		m_Shader.reset(new Shader(vertexSrc, pixelSrc));

		const std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		const std::string pixelSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;

			void main()
			{
				//colour = vec4(0.8, 0.2, 0.3, 1.0);
				colour = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_Shader2.reset(new Shader(vertexSrc2, pixelSrc2));

	}

	void Application::Run()
	{

		while (m_Running)
		{
			RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader2->Bind();
			// Draws our square
			Renderer::Submit(m_SquareVertexArray);

			m_Shader->Bind();
			// Draws our triangle
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

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
