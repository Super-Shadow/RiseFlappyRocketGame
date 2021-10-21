#include "ParticleSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Random.h"

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::Emit(const ParticleProps& props)
{
	auto& [Position, Velocity, ColourBegin, ColourEnd, SizeBegin, SizeEnd, Rotation, LifeTime, LifeRemaining, Active] = m_ParticlePool[m_PoolIndex];
	Active = true;
	Position = props.Position;
	Rotation = Random::Next() * 2.f * glm::pi<float>();

	Velocity = props.Velocity;
	Velocity.x += props.VelocityVariation.x * (Random::Next() - .5f);
	Velocity.y += props.VelocityVariation.y * (Random::Next() - .5f);

	ColourBegin = props.ColourBegin;
	ColourEnd = props.ColourEnd;

	SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Next() - .5f);
	SizeEnd = props.SizeEnd;

	LifeTime = props.LifeTime;
	LifeRemaining = LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticleSystem::OnUpdate(const Rise::TimeStep timeStep)
{
	for (auto& particle : m_ParticlePool)
	{
		if(!particle.Active)
			continue;

		if(particle.LifeRemaining <= 0.f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= timeStep;
		particle.Position += particle.Velocity * static_cast<float>(timeStep);
		particle.Rotation += .01f * timeStep;
	}
}

void ParticleSystem::OnRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		const auto life = particle.LifeRemaining / particle.LifeTime;
		auto colour = glm::lerp(particle.ColourEnd, particle.ColourBegin, life);
		colour.a = colour.a * life;

		auto size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		Rise::Renderer2D::DrawQuad(particle.Position, particle.Rotation, {size, size}, colour);
	}
}

