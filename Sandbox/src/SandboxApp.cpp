#include <Rise.h>

#include "imgui/imgui.h"

class ExampleLayer final : public Rise::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Rise::VertexArray::Create());

		// Plot our triange on X Y Z coordinates. X is horizontal and Y is vertical and Z is depth. X is -1 to 1 and Y is -1 bottom and 1 top.
		constexpr float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		std::shared_ptr<Rise::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Rise::VertexBuffer::Create(vertices, sizeof vertices));

		const Rise::BufferLayout layout = {
			{Rise::ShaderDataType::Float3, "a_Position" },
			{Rise::ShaderDataType::Float4, "a_Colour" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		constexpr uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Rise::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rise::IndexBuffer::Create(indices, static_cast<uint32_t>(std::size(indices))));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Rise::VertexArray::Create());

		constexpr float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,	 0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Rise::VertexBuffer> squareVB;
		squareVB.reset(Rise::VertexBuffer::Create(squareVertices, static_cast<uint32_t>(sizeof squareVertices)));
		squareVB->SetLayout({
			{Rise::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		constexpr uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Rise::IndexBuffer> squareIB;
		squareIB.reset(Rise::IndexBuffer::Create(squareIndices, static_cast<uint32_t>(std::size(squareIndices))));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		const std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		m_Shader.reset(new Rise::Shader(vertexSrc, pixelSrc));

		const std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		m_Shader2.reset(new Rise::Shader(vertexSrc2, pixelSrc2));
	}

	void OnUpdate(Rise::Timestep timestep) override
	{
		RS_TRACE("Delta time: {0}s ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());

		if (Rise::Input::IsKeyPressed(RS_KEY_W))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_S))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_A))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_D))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_R))
		{
			m_Camera.SetPosition({ 0, 0, 0 });
			m_Camera.SetRotation(0);
		}

		Rise::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Rise::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rise::Renderer::BeginScene(m_Camera);

		m_Shader2->Bind();
		// Draws our square
		Rise::Renderer::Submit(m_Shader2, m_SquareVertexArray);
		m_Shader->Bind();
		// Draws our triangle
		Rise::Renderer::Submit(m_Shader, m_VertexArray);

		Rise::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Rise::Event& event) override
	{
	}

private:
	std::shared_ptr<Rise::Shader> m_Shader;
	std::shared_ptr<Rise::VertexArray> m_VertexArray;

	std::shared_ptr<Rise::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Rise::Shader> m_Shader2;
	Rise::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation= 0.0f;
	float m_CameraRotationSpeed = 100.0f;
};

class Sandbox final : public Rise::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() override
	= default;
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}