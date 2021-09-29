#pragma once

#include "RendererAPI.h"

namespace Rise
{
	class RenderCommand
	{
	public:
		static void Init() { s_RendererAPI->Init(); }

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static void SetClearColour(const glm::vec4& colour) { s_RendererAPI->SetClearColour(colour); }
		static void Clear() { s_RendererAPI->Clear(); }

		static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}
