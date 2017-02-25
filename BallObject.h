#pragma once

#include "GameObject.h"

class Texture;

struct BallObject : public GameObject
{
	glm::vec2 m_velocity;
	float m_radius;
	bool m_bIsStuck = true;
	
	BallObject(Texture* const texture, const glm::vec2& position, 
		const float& radius, const glm::vec2& m_velocity = glm::vec2(100, -300));
	~BallObject() = default;

	void Reset(const glm::vec2& position, const glm::vec2& speed);
	void Move(const float& deltaTime, const int& gameWidth, const int& gameHeight);
};
