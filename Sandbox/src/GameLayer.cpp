#include "GameLayer.h"

#include "Random.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"

using namespace Rise;

GameLayer::GameLayer() : Layer("GameLayer")
{
	const auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	const auto io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(const TimeStep timeStep)
{
	m_Time += timeStep;
	if (static_cast<int>(m_Time * 10.f) % 8 > 4)
		m_Blink = !m_Blink;

	if(m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.f });

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(timeStep);
			break;
		}
		
	}

	RenderCommand::SetClearColour({ 0.f, 0.f, 0.f, 1 });
	RenderCommand::Clear();

	Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	/*
	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();*/


	const auto fps = std::string("FPS: ") + std::to_string(static_cast<int>(std::floor(ImGui::GetIO().Framerate)));
	ImGui::GetForegroundDrawList()->AddText(m_Font, 48.f, { ImGui::GetWindowPos().x - 50, ImGui::GetWindowPos().y - 50}, 0xffffffff, fps.c_str());

	switch (m_State)
	{
		case GameState::Play:
		{
			const auto playerScore = m_Level.GetPlayer().GetScore();
			const auto scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			const auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += static_cast<float>(width) * .5f - 300.f;
			pos.y += 50.f;
			if(m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			const auto width = Application::Get().GetWindow().GetWidth();
			pos.x += static_cast<float>(width) * .5f - 300.f;
			pos.y += 50.f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.f;
			pos.y += 150.f;

			const auto playerScore = m_Level.GetPlayer().GetScore();
			const auto scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.f, pos, 0xffffffff, scoreStr.c_str());

			break;
		}
	}
}

void GameLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(RS_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(RS_BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
}

bool GameLayer::OnMouseButtonPressedEvent(const Rise::MouseButtonPressedEvent& e)
{
	if(m_State == GameState::GameOver)
		m_Level.Reset();
	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(const WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(const uint32_t width, const uint32_t height)
{
	const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	constexpr auto camHeight = 8.f;
	constexpr auto bottom = -camHeight;
	constexpr auto top = camHeight;
	const auto left = bottom * aspectRatio;
	const auto right = top * aspectRatio;

	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
