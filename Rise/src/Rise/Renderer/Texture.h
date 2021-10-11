#pragma once

#include "Rise/Core/Core.h"
#include <string>

namespace Rise
{
	class Texture
	{
	public:
		Texture(const Texture&) = delete;
		Texture& operator= (const Texture&) = delete;

		Texture(Texture&&) = delete;
		Texture& operator=(Texture&&) = delete;

		virtual ~Texture() = default;

		[[nodiscard]] virtual uint32_t GetWidth() const abstract;
		[[nodiscard]] virtual uint32_t GetHeight() const abstract;

		virtual void SetData(void* data, uint32_t size) abstract;

		virtual void Bind(uint32_t slot = 0) const abstract;
	protected:
		Texture() = default;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);

	};
}
