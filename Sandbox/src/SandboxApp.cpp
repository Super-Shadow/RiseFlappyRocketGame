#include <Rise.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer final : public Rise::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Rise::VertexArray::Create());

		// Plot our triange on X Y Z coordinates. X is horizontal and Y is vertical and Z is depth. X is -1 to 1 and Y is -1 bottom and 1 top.
		constexpr float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		Rise::Ref<Rise::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Rise::VertexBuffer::Create(vertices, sizeof vertices));

		const Rise::BufferLayout layout = {
			{Rise::ShaderDataType::Float3, "a_Position" },
			{Rise::ShaderDataType::Float4, "a_Colour" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		constexpr uint32_t indices[3] = { 0, 1, 2 };
		Rise::Ref<Rise::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rise::IndexBuffer::Create(indices, static_cast<uint32_t>(std::size(indices))));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Rise::VertexArray::Create());

		constexpr float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,	0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Rise::Ref<Rise::VertexBuffer> squareVB;
		squareVB.reset(Rise::VertexBuffer::Create(squareVertices, static_cast<uint32_t>(sizeof squareVertices)));
		squareVB->SetLayout({
			{Rise::ShaderDataType::Float3, "a_Position" },
			{Rise::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		constexpr uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rise::Ref<Rise::IndexBuffer> squareIB;
		squareIB.reset(Rise::IndexBuffer::Create(squareIndices, static_cast<uint32_t>(std::size(squareIndices))));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		const std::string vertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		const std::string pixelSrc = R"(
			#version 460 core

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
		m_Shader.reset(Rise::Shader::Create(vertexSrc, pixelSrc));
		// -------------------------------------------------------------------------------------

		const std::string flatVertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		const std::string flatPixelSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;

			uniform vec3 u_Colour;

			void main()
			{
				colour = vec4(u_Colour, 1.0);
			}
		)";
		m_FlatShader.reset(Rise::Shader::Create(flatVertexSrc, flatPixelSrc));
		// -------------------------------------------------------------------------------------

		const std::string textureVertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		const std::string texturePixelSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 colour;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				//colour = vec4(v_TexCoord, 0.0, 1.0);
				colour = texture(u_Texture, v_TexCoord);
			}
		)";
		m_TextureShader.reset(Rise::Shader::Create(textureVertexSrc, texturePixelSrc));
		// -------------------------------------------------------------------------------------

		m_Texture = Rise::Texture2D::Create("assets/textures/Checkerboard.png");
		std::dynamic_pointer_cast<Rise::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Rise::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(const Rise::Timestep timestep) override
	{
		RS_TRACE("Delta time: {0}s ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());

		if (Rise::Input::IsKeyPressed(RS_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		if (Rise::Input::IsKeyPressed(RS_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
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
			m_Camera.SetRotation(0);\
		}

		Rise::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Rise::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rise::Renderer::BeginScene(m_Camera);

		const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Rise::OpenGLShader>(m_FlatShader)->Bind();
		std::dynamic_pointer_cast<Rise::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Colour", m_SquareColour);

		for (float y = 0; y < 20; ++y)
		{
			for (float x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				const glm::mat4 transform = translate(glm::mat4(1.0f), pos) * scale;
				// Draws our square
				Rise::Renderer::Submit(m_FlatShader, m_SquareVertexArray, transform);
			}
		}

		m_Texture->Bind();
		Rise::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Draws our triangle
		//Rise::Renderer::Submit(m_Shader, m_VertexArray);

		Rise::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colour", value_ptr(m_SquareColour));
		ImGui::End();
	}

	void OnEvent(Rise::Event& event) override
	{
	}

private:
	Rise::Ref<Rise::Shader> m_Shader;
	Rise::Ref<Rise::VertexArray> m_VertexArray;

	Rise::Ref<Rise::VertexArray> m_SquareVertexArray;
	Rise::Ref<Rise::Shader> m_FlatShader, m_TextureShader;

	Rise::Ref<Rise::Texture2D> m_Texture;

	Rise::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation= 0.0f;
	float m_CameraRotationSpeed = 100.0f;

	glm::vec3 m_SquareColour = { 0.2f, 0.3f, 0.8f };

};

class Sandbox final : public Rise::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() override = default;
};

Rise::Application* Rise::CreateApplication()
{
	return new Sandbox();
}