#include "rspch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Rise
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		// Pass our triangle into buffer. Static draw since it wont change at runtime.
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// TODO: Snus seperate these into their own files 

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count) : m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		// Pass our drawing order into buffer. Static draw since it wont change at runtime.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
