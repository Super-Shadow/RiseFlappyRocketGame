#include "Player.h"

#include "imgui/imgui.h"
#include <glm/gtx/transform.hpp>

using namespace Rise;

Player::Player()
{
	m_SmokeParticle.Position = {0.f, 0.f};
	m_SmokeParticle.Velocity = {-2.f, 0.f};
	m_SmokeParticle.VelocityVariation = { 4.f, 2.f};
	m_SmokeParticle.SizeBegin = .35f;
	m_SmokeParticle.SizeEnd = 0.f;
	m_SmokeParticle.SizeVariation = .15f;
	m_SmokeParticle.ColourBegin = {.8f, .8f, .8f, 1.f};
	m_SmokeParticle.ColourEnd = {.6f, .6f, .6f, 1.f};
	m_SmokeParticle.LifeTime = 4.f;

	m_EngineParticle.Position = { 0.f, 0.f };
	m_EngineParticle.Velocity = { -2.f, 0.f };
	m_EngineParticle.VelocityVariation = { 3.f, 1.f };
	m_EngineParticle.SizeBegin = .5f;
	m_EngineParticle.SizeEnd = 0.f;
	m_EngineParticle.SizeVariation = .3f;
	m_EngineParticle.ColourBegin = { 254 / 255.f, 109 / 255.f, 41 / 255.f, 1.f };
	m_EngineParticle.ColourEnd = { 254 / 255.f, 212 / 255.f, 123 / 255.f, 1.f };
	m_EngineParticle.LifeTime = 1.f;
}

void Player::LoadAssets()
{
	m_ShipTexture = Texture2D::Create("assets/textures/ship.png");
}

void Player::OnUpdate(const TimeStep timeStep)
{
	m_Time += timeStep;

	if (Input::IsKeyPressed(RS_KEY_SPACE))
	{
		m_Velocity.y += m_EnginePower;
		if (m_Velocity.y < 0.f)
			m_Velocity.y += m_EnginePower * 2.f;

		constexpr glm::vec2 emissionPoint = {0.f, -0.6f};
		const auto rotation = glm::radians(GetRotation());
		const glm::vec4 rotated = glm::rotate(glm::mat4(1.f), rotation, {.0f, .0f, 1.f}) * glm::vec4(emissionPoint, 0.f, 1.f);


		m_EngineParticle.Position = m_Position + glm::vec2{rotated.x, rotated.y};
		m_EngineParticle.Velocity.y = -m_Velocity.y * .2f - .2f;
		m_ParticleSystem.Emit(m_EngineParticle);
	}
	else
	{
		m_Velocity.y -= m_Gravity;
	}

	m_Velocity.y = glm::clamp(m_Velocity.y, -20.f, 20.f);
	m_Position += m_Velocity * static_cast<float>(timeStep);

	if(m_Time > m_SmokeNextEmitTime)
	{
		m_SmokeParticle.Position = m_Position;
		m_ParticleSystem.Emit(m_SmokeParticle);
		m_SmokeNextEmitTime += m_SmokeEmitInterval;
	}

	m_ParticleSystem.OnUpdate(timeStep);
}

void Player::OnRender()
{
	m_ParticleSystem.OnRender();
	Renderer2D::DrawQuad({m_Position.x, m_Position.y, .5f}, glm::radians(GetRotation()), { .9f, 1.3f }, m_ShipTexture);
}

void Player::OnImGuiRender()
{
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);
}

void Player::Reset()
{
	m_Position = { -10.f, 0.f };
	m_Velocity = { 5.f, 0.f };

}
