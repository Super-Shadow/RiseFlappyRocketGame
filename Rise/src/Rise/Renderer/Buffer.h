#pragma once

namespace Rise
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;

		static VertexBuffer* Create(const float* vertices, const uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;

		virtual uint32_t GetCount() const abstract;

		static IndexBuffer* Create(const uint32_t* indices, const uint32_t count);

	};
}
