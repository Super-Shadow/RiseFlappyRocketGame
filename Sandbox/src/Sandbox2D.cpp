#include "Sandbox2D.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Rise::VertexArray::Create();

	constexpr float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		 0.5f,	0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f
	};
	
	const Rise::Ref<Rise::VertexBuffer> squareVB = Rise::VertexBuffer::Create(squareVertices, static_cast<uint32_t>(sizeof squareVertices));
	squareVB->SetLayout({ {Rise::ShaderDataType::Float3, "a_Position" } });
	
	m_SquareVertexArray->AddVertexBuffer(squareVB);
	
	constexpr uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	const Rise::Ref<Rise::IndexBuffer> squareIB = Rise::IndexBuffer::Create(squareIndices, static_cast<uint32_t>(std::size(squareIndices)));
	m_SquareVertexArray->SetIndexBuffer(squareIB);
	
	m_FlatColourShader = Rise::Shader::Create("assets/shaders/FlatColour.glsl");
}
void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(const Rise::TimeStep timeStep)
{
	// Update
	m_CameraController.OnUpdate(timeStep);

	// Render
	Rise::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
	Rise::RenderCommand::Clear();

	Rise::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Rise::OpenGLShader>(m_FlatColourShader)->Bind();
	std::dynamic_pointer_cast<Rise::OpenGLShader>(m_FlatColourShader)->UploadUniformFloat4("u_Colour", m_SquareColour);

	Rise::Renderer::Submit(m_FlatColourShader, m_SquareVertexArray, scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Rise::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", value_ptr(m_SquareColour));
	ImGui::End();
}

void Sandbox2D::OnEvent(Rise::Event& e)
{
	m_CameraController.OnEvent(e);

}
