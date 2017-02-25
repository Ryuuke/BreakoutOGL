#include "DrawableComponent.h"
#include <gl/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "Shader.h"
#include "IShape.h"
#include "Transform2DComponent.h"

void DrawableComponent::VDraw(const Transform2DComponent& transform)
{
	m_shader->Use();

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(transform.m_position, 0.0));

	model = glm::translate(model, glm::vec3(0.5 * transform.m_size.x, 0.5 * transform.m_size.y, 0.0));
	model = glm::rotate(model, glm::radians(transform.m_rotation), glm::vec3(0, 0, 1.f));
	model = glm::translate(model, glm::vec3(-0.5 * transform.m_size.x, -0.5 * transform.m_size.y, 0.0));

	model = glm::scale(model, glm::vec3(transform.m_size, 1.f));

	m_shader->SetMatrix4("model", model);
	m_shader->SetVector3f("spriteColor", m_color);

	glActiveTexture(GL_TEXTURE0);
	m_texture->Bind();

	glBindVertexArray(m_shape->VGetVao());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
