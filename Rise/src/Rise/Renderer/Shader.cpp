#include "rspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Rise
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				RS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSrc, pixelSrc);
		}

		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
