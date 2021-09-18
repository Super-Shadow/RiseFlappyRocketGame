#pragma once

namespace Rise
{
	class GraphicsContext
	{
	public:
		virtual void Init() abstract;
		virtual void SwapBuffers() abstract;
	};
}
