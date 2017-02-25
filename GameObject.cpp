#include "GameObject.h"
#include "SpriteRenderer.h"

GameObject::GameObject(Texture * const texture, const glm::vec2 & position, 
	const glm::vec2 & size, const glm::vec3& color, const float& rotation)
	: m_texture(texture), m_position(position), m_size(size), m_color(color), m_rotation(rotation)
{
}

void GameObject::VDraw(const SpriteRenderer& spriteRenderer)
{
	if (m_bIsDead)
		return;

	spriteRenderer.VDraw(m_texture, m_position, m_size, m_rotation, m_color);
}
