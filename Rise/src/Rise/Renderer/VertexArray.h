#pragma once
#include "Buffer.h"

namespace Rise
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) abstract;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) abstract;

		[[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const abstract;
		[[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const abstract;

		static VertexArray* Create();
	};
}
