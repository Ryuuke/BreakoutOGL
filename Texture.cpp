#include "Texture.h"
#include "SOIL/SOIL.h"

void Texture::Destroy()
{
	if (m_textureId)
		glDeleteTextures(1, &m_textureId);
}

void Texture::Init(const char * texturePath, const bool bUseAlpha)
{
	glGenTextures(1, &m_textureId);

	glBindTexture(GL_TEXTURE_2D, m_textureId);

	auto imageData = SOIL_load_image(texturePath, &m_width, &m_height, nullptr, 
		bUseAlpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, bUseAlpha ? GL_RGBA : GL_RGB, 
		m_width, m_height, 0, bUseAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
}

