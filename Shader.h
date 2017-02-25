#pragma once

#include "GL/glew.h"
#include "GLM/glm.hpp"
#include <string>

class Shader
{
private:
	GLuint m_program = 0;
public:
	Shader() = default;
	~Shader() = default;
	
	void Init(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Destroy();

	inline void Use() const { glUseProgram(m_program); }

	void SetFloat(const char* location, const float& value) const;
	void SetInt(const char* location, const int& value) const;

	void SetVector2f(const char* location, const float& x, const float& y) const;
	void SetVector2f(const char* location, glm::vec2& vec2) const;

	void SetVector3f(const char* location, const float& x, const float& y, const float& z) const;
	void SetVector3f(const char* location, const glm::vec3& vec3) const;

	void SetVector4f(const char* location, const float& x, const float& y, const float& z, const float& w) const;
	void SetVector4f(const char* location, const glm::vec4& vec4) const;

	void SetMatrix4(const char* location, const glm::mat4& mat4) const;

private:
	std::string ReadFile(const char* file) const;
	void CompileShader(const GLuint& shader, const char* path) const;
	void CreateProgram(const GLuint& vxShader, const GLuint& fxShader);
};

