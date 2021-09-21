#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Rise
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& pixelSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void HandleShaderFailure(const std::string& assertMessage, const unsigned int* vertexShader, const unsigned int* pixelShader = nullptr) const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
	private:
		uint32_t m_RendererID;
	};
}
