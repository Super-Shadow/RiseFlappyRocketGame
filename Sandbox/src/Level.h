#pragma once
#include "Player.h"

struct Pillar
{
	glm::vec3 TopPosition{ 0.f, 10.f, 0.f };
	glm::vec2 TopScale{ 15.f, 20.f };

	glm::vec3 BottomPosition{ 10.f, 10.f, 0.f };
	glm::vec2 BottomScale{ 15.f, 20.f };
};

class Level
{
public:
	Level();

	void Init();

	void OnUpdate(Rise::TimeStep timeStep);
	void OnRender();
	void OnImGuiRender();

	void Reset();

	[[nodiscard]] bool IsGameOver() const { return m_GameOver; }

	[[nodiscard]] Player& GetPlayer() { return m_Player; }

private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();

	void GameOver();

	Player m_Player;

	bool m_GameOver = false;

	float m_PillarTarget = 30.f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = {0.f, .8f, .8f};

	std::vector<Pillar> m_Pillars;
	std::vector<glm::vec2> m_Points;

	Rise::Ref<Rise::Texture2D> m_TriangleTexture;
};
