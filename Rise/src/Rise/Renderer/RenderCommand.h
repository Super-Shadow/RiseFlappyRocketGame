#pragma once

#include "RendererAPI.h"

namespace Rise
{
	class RenderCommand
	{
	public:
		static void SetClearColour(const glm::vec4& colour) { s_RendererAPI->SetClearColour(colour); }
		static void Clear() { s_RendererAPI->Clear(); }

		static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* s_RendererAPI;
	};
}
