#pragma once

#include "GL/glew.h"

class Texture
{
	GLuint m_textureId = 0;
	int m_width = 0;
	int m_height = 0;
public:
	Texture() = default;
	~Texture() = default;

	void Init(const char* texturePath, const bool bUseAlpha);
	void Destroy();

	inline void Bind() const { glBindTexture(GL_TEXTURE_2D, m_textureId); }
};
