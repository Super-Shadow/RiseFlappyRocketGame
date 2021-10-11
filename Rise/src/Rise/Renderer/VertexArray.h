#pragma once
#include "Buffer.h"

namespace Rise
{
	class VertexArray
	{
	public:
		VertexArray(VertexArray const&) = delete;
		VertexArray& operator=(VertexArray const&) = delete;

		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) abstract;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) abstract;

		[[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const abstract;
		[[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const abstract;

		static Ref<VertexArray> Create();

	protected:
		VertexArray() = default;
		virtual ~VertexArray() = default;
	};
}
