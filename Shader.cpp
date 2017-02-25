#include "Shader.h"

#include <fstream>
#include <iostream>
#include "GLM/gtc/type_ptr.hpp"

void Shader::Destroy()
{
	if (m_program)
		glDeleteProgram(m_program);
}

void Shader::Init(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	GLuint vxShader = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(vxShader, vertexShaderPath);

	GLuint fxShader = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(fxShader, fragmentShaderPath);

	CreateProgram(vxShader, fxShader);

	glDeleteShader(fxShader);
	glDeleteShader(vxShader);
}

std::string Shader::ReadFile(const char* file) const
{
	std::ifstream fileReader;
	fileReader.open(file, std::ios::ate | std::ios::binary);
	
	assert(fileReader.good());

	size_t fileSize = fileReader.tellg();

	fileReader.seekg(0, std::ios::beg);

	std::string fileContent;

	fileContent.resize(fileSize);

	fileReader.read(&fileContent[0], fileSize);

	return fileContent;
}

void Shader::CompileShader(const GLuint& shader, const char* path) const
{
	auto shaderDataString = ReadFile(path);

	char* shaderData = &shaderDataString[0];

	glShaderSource(shader, 1, &shaderData, nullptr);

	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	char infoLog[1024];

	if (success)
		return;

	glGetShaderInfoLog(shader, 1024, NULL, infoLog);
	std::cout << "filename: " << path << "\n";
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}

void Shader::CreateProgram(const GLuint& vxShader, const GLuint& fxShader)
{
	m_program = glCreateProgram();

	glAttachShader(m_program, vxShader);
	glAttachShader(m_program, fxShader);

	glLinkProgram(m_program);

	GLint success;
	char infoLog[1024];

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (success)
		return;

	glGetProgramInfoLog(m_program, 1024, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}

void Shader::SetFloat(const char * location, const float & value) const
{
	glUniform1f(glGetUniformLocation(m_program, location), value);
}

void Shader::SetInt(const char * location, const int & value) const
{
	glUniform1i(glGetUniformLocation(m_program, location), value);
}

void Shader::SetVector2f(const char * location, const float & x, const float & y) const
{
	glUniform2f(glGetUniformLocation(m_program, location), x, y);
}

void Shader::SetVector2f(const char * location, glm::vec2& vec2) const
{
	glUniform2f(glGetUniformLocation(m_program, location), vec2.x, vec2.y);
}

void Shader::SetVector3f(const char * location, const float & x, const float & y, const float & z) const
{
	glUniform3f(glGetUniformLocation(m_program, location), x, y, z);
}

void Shader::SetVector3f(const char * location, const glm::vec3& vec3) const
{
	glUniform3f(glGetUniformLocation(m_program, location), vec3.x, vec3.y, vec3.z);
}

void Shader::SetVector4f(const char * location, const float & x, const float & y, const float & z, const float & w) const
{
	glUniform4f(glGetUniformLocation(m_program, location), x, y, z, w);
}

void Shader::SetVector4f(const char * location, const glm::vec4& vec4) const
{
	glUniform4f(glGetUniformLocation(m_program, location), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::SetMatrix4(const char * location, const glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, location), 1, GL_FALSE, glm::value_ptr(mat4));
}

