#pragma once

namespace Rise
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const abstract;
		virtual void Unbind() const abstract;
		virtual void HandleShaderFailure(const std::string& assertMessage, const unsigned int* vertexShader, const unsigned int* pixelShader = nullptr) const abstract;

		static Shader* Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};
}
