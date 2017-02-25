#include "SpriteRenderer.h"

#include <GLM/gtc/matrix_transform.hpp>

void SpriteRenderer::Destroy()
{
	if (m_quadVao)
		glDeleteVertexArrays(1, &m_quadVao);
}

void SpriteRenderer::Init()
{
	GLfloat vertices[] =
	{
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &m_quadVao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(m_quadVao);

	{
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void SpriteRenderer::VDraw(const Texture* const texture, const glm::vec2& position, 
	const glm::vec2& size, const float& rotation, const glm::vec3& color) const
{
	m_shader->Use();

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position, 0.0));

	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1.f));
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0));

	model = glm::scale(model, glm::vec3(size, 1.f));

	m_shader->SetMatrix4("model", model);
	m_shader->SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	glBindVertexArray(m_quadVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
