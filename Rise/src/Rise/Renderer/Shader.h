#pragma once

namespace Rise
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;

		static Shader* Create(const std::string& filePath);
		static Shader* Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};
}
