#include "rspch.h"
#include "RenderCommand.h"

namespace Rise
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
