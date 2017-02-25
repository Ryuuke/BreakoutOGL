#pragma once

#include <GLM/glm.hpp>
#include "Texture.h"

class SpriteRenderer;

struct GameObject
{
	Texture* m_texture;
	glm::vec3 m_color;
	bool m_bIsDead = false;
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation = 0;
	bool m_bIsBlock = false;

	GameObject(Texture* const texture, const glm::vec2& position, const glm::vec2& size, const glm::vec3& color = glm::vec3(1.f), const float& rotation = 0);
	~GameObject() = default;

	virtual void VDraw(const SpriteRenderer& spriteRenderer);
};
