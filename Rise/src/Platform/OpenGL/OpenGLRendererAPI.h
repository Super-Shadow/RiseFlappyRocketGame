#pragma once
#include "Rise/Renderer/RendererAPI.h"

namespace Rise
{
	class OpenGLRendererAPI final : public RendererAPI
	{
	public:
		void SetClearColour(const glm::vec4& colour) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
