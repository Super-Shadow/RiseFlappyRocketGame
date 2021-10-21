#pragma once

#include <Rise.h>
#include "Colour.h"
#include "ParticleSystem.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Rise::TimeStep timeStep);
	void OnRender();

	void OnImGuiRender();

	void Reset();

	[[nodiscard]] glm::vec2 GetPosition() const { return m_Position; }
	[[nodiscard]] float GetRotation() const { return m_Velocity.y * 4.f - 90.f; }

	[[nodiscard]] uint32_t GetScore() const { return static_cast<uint32_t>(m_Position.x + 10.f) / 10; }

private:
	glm::vec2 m_Position{ -10.f, 0.f };
	glm::vec2 m_Velocity{ 5.f, 0.f };

	float m_EnginePower = 0.5f;
	float m_Gravity = .4f;

	float m_Time = 0.f;
	float m_SmokeEmitInterval = .4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Rise::Ref<Rise::Texture2D> m_ShipTexture;
};
