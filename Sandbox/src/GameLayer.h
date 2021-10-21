#pragma once
#include "Level.h"
#include "Rise.h"
#include "imgui/imgui.h"

class GameLayer final : public Rise::Layer
{
public:
	GameLayer();

	GameLayer(const GameLayer&) = delete;
	GameLayer& operator=(const GameLayer&) = delete;

	GameLayer(GameLayer&&) = delete;
	GameLayer& operator=(GameLayer&&) = delete;

	~GameLayer() override = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(const Rise::TimeStep timeStep) override;
	void OnImGuiRender() override;
	void OnEvent(Rise::Event& e) override;
	bool OnMouseButtonPressedEvent(const Rise::MouseButtonPressedEvent& e);
	bool OnWindowResize(const Rise::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

	Rise::Scope<Rise::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0,
		MainMenu = 1,
		GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
