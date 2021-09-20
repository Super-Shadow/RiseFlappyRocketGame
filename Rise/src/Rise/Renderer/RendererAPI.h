#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Rise
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void SetClearColour(const glm::vec4& colour) abstract;
		virtual void Clear() abstract;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) abstract;

		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}
