#include "BallObject.h"

BallObject::BallObject(Texture* const texture, const glm::vec2 & position, const float & radius, const glm::vec2 & velocity)
	: GameObject(texture, position, glm::vec2(radius * 2, radius * 2)), m_radius(radius), m_velocity(velocity)
{
}

void BallObject::Reset(const glm::vec2 & position, const glm::vec2 & speed)
{
	m_bIsStuck = true;
	m_position = position;
	m_velocity = speed;
}

void BallObject::Move(const float & deltaTime, const int & gameWidth, const int & gameHeight)
{
	if (m_bIsStuck)
		return;

	glm::vec2 velocity = m_velocity * deltaTime;

	glm::vec2 nextPosition = m_position + velocity;

	if (nextPosition.x + m_size.x >= gameWidth )
	{
		nextPosition.x = gameWidth - m_size.x;
		m_velocity.x = -m_velocity.x;
	}

	if (nextPosition.x <= 0)
	{
		nextPosition.x = 0;
		m_velocity.x = -m_velocity.x;
	}

	if (nextPosition.y <= 0)
	{
		nextPosition.y = 0;
		m_velocity.y = -m_velocity.y;
	}

	m_position.x = nextPosition.x;
	m_position.y = nextPosition.y;
}
