#include "rspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Rise
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				return GL_FLOAT;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
				return GL_INT;
			case ShaderDataType::Bool:
				return GL_BOOL;
			default:
			{
				RS_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}
		}
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		RS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			// Tell openGL that the bytes just passed in are 3 vec3's
			glEnableVertexAttribArray(index); // Enable index 0 (first param of next line) of our attrib data

			// First param is the index, next two params are telling it that the bytes are 3 floats. Next param is telling it that they are not normalised.
			// Next param is the amount of bytes between the vertices (So the space for each vertex aka 3(each point for triangle) * 4(size of a float).
			// Last param is the offset for this specific attribute when it is applied to our vertices data thing. We want it to start at the beginning of each vec3 coordinate.
			glVertexAttribPointer(index, static_cast<int>(element.GetComponentCount()), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE, static_cast<int>(layout.GetStride()), reinterpret_cast<const void*>(element.Offset));  // NOLINT(performance-no-int-to-ptr, performance-no-int-to-ptr)

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
