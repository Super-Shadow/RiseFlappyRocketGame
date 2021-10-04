#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Rise
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void Init() abstract;
		virtual ~RendererAPI() = default;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) abstract;
		virtual void SetClearColour(const glm::vec4& colour) abstract;
		virtual void Clear() abstract;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) abstract;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	private:
		static API s_API;
	};
}
