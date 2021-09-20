#include "rspch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Rise
{
	Shader::Shader(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		// Create an empty vertex shader handle
		const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		auto source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			HandleShaderFailure("Vertex shader compilation failure!", &vertexShader);
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = pixelSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, nullptr);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			HandleShaderFailure("Pixel/Fragment shader compilation failure!", &vertexShader, &fragmentShader);
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		const auto program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			RS_CORE_ERROR("{0}", infoLog.data());
			RS_CORE_ASSERT(false, "Shader link failure!")

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::HandleShaderFailure(const std::string& assertMessage, const GLuint* vertexShader, const GLuint* pixelShader) const
	{
		GLint maxLength;
		glGetShaderiv(pixelShader == nullptr ? *vertexShader : *pixelShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(pixelShader == nullptr ? *vertexShader : *pixelShader, maxLength, &maxLength, &infoLog[0]);

		if (pixelShader != nullptr)
		{
			// We don't need the shader anymore.
			glDeleteShader(*pixelShader);
		}
		// Either of them. Don't leak shaders.
		glDeleteShader(*vertexShader);

		// Use the infoLog as you see fit.
		RS_CORE_ERROR("{0}", infoLog.data());
		RS_CORE_ASSERT(false, assertMessage)
	}
}
