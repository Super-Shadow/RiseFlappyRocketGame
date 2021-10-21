#pragma once
#include "Rise.h"

struct ParticleProps
{
	glm::vec2 Position, Velocity, VelocityVariation;
	glm::vec4 ColourBegin, ColourEnd;
	float SizeBegin, SizeEnd, SizeVariation, LifeTime = 1.f;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void Emit(const ParticleProps& props);

	void OnUpdate(Rise::TimeStep timeStep);
	void OnRender();

private:
	struct Particle
	{
		glm::vec2 Position, Velocity;
		glm::vec4 ColourBegin, ColourEnd;
		float SizeBegin, SizeEnd, Rotation = 0.f, LifeTime = 1.f, LifeRemaining = 0.f;
		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
};
