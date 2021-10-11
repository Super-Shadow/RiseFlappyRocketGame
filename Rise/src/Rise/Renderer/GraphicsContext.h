#pragma once

namespace Rise
{
	class GraphicsContext
	{
	public:
		GraphicsContext(const GraphicsContext&) = delete;
		GraphicsContext& operator= (const GraphicsContext&) = delete;

		GraphicsContext(GraphicsContext&&) = delete;
		GraphicsContext& operator=(GraphicsContext&&) = delete;

		virtual ~GraphicsContext() = default;

		virtual void Init() abstract;
		virtual void SwapBuffers() abstract;

		static Scope<GraphicsContext> Create(void* window);
	protected:
		GraphicsContext() = default;
	};
}
