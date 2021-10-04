#include "Sandbox2D.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"

template<typename Fn>
class Timer // Set time when object is created, then once scope finishes this is destroyed and calls Stop()
{
public:
	Timer(const char* name, Fn&& func) : m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		const auto endTimePoint = std::chrono::high_resolution_clock::now();

		const auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		const auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f; // Convert microseconds to milliseconds
		m_Func({ m_Name, duration });
		//std::cout << m_Name << ": " << duration << "ms" << std::endl;
	}

private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerBoardTexture = Rise::Texture2D::Create("assets/textures/Checkerboard.png");

}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(const Rise::TimeStep timeStep)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("m_CameraController.OnUpdate");
		m_CameraController.OnUpdate(timeStep);
	}
	// Render
	{
		PROFILE_SCOPE("RenderCommand::Clear");

		Rise::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Rise::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer2D::Scene");

		Rise::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Rise::Renderer2D::DrawQuad({ -1.f, 0.f }, { .8f, .8f }, { 0.8f, 0.2f, 0.3f, 1.f });
		Rise::Renderer2D::DrawQuad({ .5f, -0.5f }, { .5f, .75f }, { 0.2f, 0.3f, 0.8f, 1.f });
		Rise::Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 10.5f, 10.5f }, m_CheckerBoardTexture, 10);

		Rise::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", value_ptr(m_SquareColour));

	for (const auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Rise::Event& e)
{
	m_CameraController.OnEvent(e);

}
