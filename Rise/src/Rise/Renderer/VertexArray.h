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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) abstract;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) abstract;

		[[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const abstract;
		[[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const abstract;

		static VertexArray* Create();
	};
}
