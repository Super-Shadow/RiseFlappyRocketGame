#include "Level.h"

#include "Random.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Rise;

static glm::vec3 HSVtoRGB(const glm::vec3& hsv)
{
	const auto H = truncf(hsv.x * 360.0f);
	const auto S = hsv.y;
	const auto V = hsv.z;

	const auto C = S * V;
	const auto X = C * (1 - abs(fmod(H / 60.0f, 2.f) - 1));
	const auto m = V - C;
	float Rs, Gs, Bs;

	if (H >= 0 && H < 60)
	{
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120)
	{
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180)
	{
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240)
	{
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300)
	{
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else
	{
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m) };
}

static bool PointInTriangle(const glm::vec2& p, const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2 )
{
	const auto s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	const auto t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	const auto A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
	
}

Level::Level()
= default;

void Level::Init()
{
	m_TriangleTexture = Texture2D::Create("assets/textures/Triangle.png");
	m_Player.LoadAssets();

	m_Pillars.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		CreatePillar(i, i * 10.f);
	}
}

void Level::OnUpdate(const TimeStep timeStep)
{
	m_Player.OnUpdate(timeStep);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	if(m_PillarHSV.x >= 1.f)
		m_PillarHSV.x = 0.f;
	else
		m_PillarHSV.x += .1f * timeStep;

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 20.f);
		m_PillarIndex = static_cast<int>(++m_PillarIndex % m_Pillars.size()); // this will convert pillar index number to fit into the range of pillar size. 
		m_PillarTarget += 10.f;
	}
}


void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();
	const glm::vec4 colour = {HSVtoRGB(m_PillarHSV), 1.f};

	// Background
	Renderer2D::DrawQuad({ playerPos.x, 0.f, -.8f }, { 50.f, 50.f }, { .3f, .3f, .3f, 1.f });

	// Floor and ceiling
	Renderer2D::DrawQuad({ playerPos.x, 34.f }, { 50.f, 50.f }, colour);
	Renderer2D::DrawQuad({ playerPos.x, -34.f }, { 50.f, 50.f }, colour);


	for (auto& pillar : m_Pillars)
	{
		Renderer2D::DrawQuad(pillar.TopPosition, glm::radians(180.f), pillar.TopScale, m_TriangleTexture, 1.f, colour);
		Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, m_TriangleTexture, 1.f, colour);
	}

	m_Player.OnRender();

	for (auto& point : m_Points)
	{
		Renderer2D::DrawQuad({point.x, point.y, .5f}, {.1f, .1f}, Colour::Red);
	}

	m_Points.clear();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::Reset()
{
	m_GameOver = false;

	m_Player.Reset();

	m_PillarTarget = 30.f;
	m_PillarIndex = 0;
	for (int i = 0; i < 5; ++i)
	{
		CreatePillar(i, i * 10.f);
	}
}

void Level::CreatePillar(const int index, const float offset)
{
	auto& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = static_cast<float>(index) * .1f - .5f;
	pillar.BottomPosition.z = static_cast<float>(index) * .1f - .5f;

	const auto centre = Random::Next() * 35.f - 17.5f;
	const auto gap = 2.f + Random::Next() * 5.f;

	pillar.TopPosition.y = 10.f - (10.f - centre) * .2f + gap * .5f;
	pillar.BottomPosition.y = -10.f - (-10.f - centre) * .2f - gap * .5f;
}

bool Level::CollisionTest()
{
	constexpr glm::vec4 playerVertices[4] = {
	{-0.5f, -0.5f, 0.0f, 1.f },
	{ 0.5f, -0.5f, 0.0f, 1.f },
	{ 0.5f,  0.5f, 0.0f, 1.f },
	{-0.5f,  0.5f, 0.0f, 1.f }
	};

	const auto& pos = m_Player.GetPosition();
	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; ++i)
	{
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.f), {pos.x, pos.y, 0.f} )
		* glm::rotate(glm::mat4(1.f), glm::radians(m_Player.GetRotation()), {0.f, 0.f, 1.f})
		* glm::scale(glm::mat4(1.f), {.9f, 1.3f, 1.f}) * playerVertices[i];

		m_Points.emplace_back(playerTransformedVerts[i].x, playerTransformedVerts[i].y);
	}


	// Match Triangle.png (each corner is 10% from texture edge)
	constexpr glm::vec4 pillarVertices[3] = {
	{-0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.f },
	{ 0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.f },
	{ 0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.f }
	};

	for (auto& pillar : m_Pillars)
	{
		glm::vec2 tri[3];

		// Top Pillars
		for (int i = 0; i < 3; ++i)
		{
			tri[i] = glm::translate(glm::mat4(1.f), { pillar.TopPosition.x, pillar.TopPosition.y, 0.f })
			* glm::rotate(glm::mat4(1.f), glm::radians(180.f), { 0.f, 0.f, 1.f })
			* glm::scale(glm::mat4(1.f), { pillar.TopScale.x, pillar.TopScale.y, 1.f }) * pillarVertices[i];

			m_Points.emplace_back(tri[i].x, tri[i].y);
		}

		for (auto& vert : playerTransformedVerts)
		{
			if(PointInTriangle({vert.x, vert.y}, tri[0], tri[1], tri[2]))
				return true;
		}

		// Bottom Pillars
		for (int i = 0; i < 3; ++i)
		{
			tri[i] = glm::translate(glm::mat4(1.f), { pillar.BottomPosition.x, pillar.BottomPosition.y, 0.f })
			* glm::scale(glm::mat4(1.f), { pillar.BottomScale.x, pillar.BottomScale.y, 1.f }) * pillarVertices[i];

			m_Points.emplace_back(tri[i].x, tri[i].y);
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTriangle({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

	}
	return false;

}

void Level::GameOver()
{
	m_GameOver = true;
}
