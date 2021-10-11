#pragma once
#include "Rise/Renderer/Buffer.h"

namespace Rise
{
	class OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices, uint32_t size);

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

		OpenGLVertexBuffer(OpenGLVertexBuffer&&) = delete;
		OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&&) = delete;

		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer final : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);

		OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;

		OpenGLIndexBuffer(OpenGLIndexBuffer&&) = delete;
		OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&&) = delete;

		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] uint32_t GetCount() const override { return m_Count;  }
	private:
		uint32_t m_RendererID, m_Count;
	};
}
