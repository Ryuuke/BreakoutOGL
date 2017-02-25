#include "Transform2DComponent.h"

float Transform2DComponent::GetDistance(const glm::vec2 & otherPosition) const
{
	return glm::length(m_position - otherPosition);
}

void Transform2DComponent::MoveBy(const float & x, const float & y)
{
	m_position.x += x;
	m_position.y += y;
}

void Transform2DComponent::MoveBy(const glm::vec2 & distance)
{
	m_position.x += distance.x;
	m_position.y += distance.y;
}
