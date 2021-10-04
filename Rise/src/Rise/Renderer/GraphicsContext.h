#pragma once

namespace Rise
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() abstract;
		virtual void SwapBuffers() abstract;

		static Scope<GraphicsContext> Create(void* window);
	};
}
