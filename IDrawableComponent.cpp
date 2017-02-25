#include "IDrawableComponent.h"

IDrawableComponent::IDrawableComponent(Texture * const texture, Shader * const shader, IShape * const shape, const glm::vec3& color)
	: m_texture(texture), m_shader(shader), m_shape(shape), m_color(color)
{
}
