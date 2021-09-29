#pragma once

#include "Rise/Core/Core.h"
#include <string>

namespace Rise
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const abstract;
		virtual uint32_t GetHeight() const abstract;

		virtual void Bind(uint32_t slot = 0) const abstract;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}
