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

		RendererAPI(const RendererAPI&) = delete;
		RendererAPI& operator= (const RendererAPI&) = delete;

		RendererAPI(RendererAPI&&) = delete;
		RendererAPI& operator=(RendererAPI&&) = delete;

		virtual ~RendererAPI() = default;

		virtual void Init() abstract;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) abstract;
		virtual void SetClearColour(const glm::vec4& colour) abstract;
		virtual void Clear() abstract;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) abstract;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	protected:
		RendererAPI() = default;

	private:
		static API s_API;
	};
}
