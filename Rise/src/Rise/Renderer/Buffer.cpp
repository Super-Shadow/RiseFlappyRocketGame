#include "rspch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Rise
{
	VertexBuffer* VertexBuffer::Create(const float* vertices, const uint32_t size)
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::None:
				RS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		RS_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(const uint32_t* indices, const uint32_t count)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				RS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
					return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}

		RS_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
		
	}
}
