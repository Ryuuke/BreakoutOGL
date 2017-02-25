#pragma once

#include "IActorComponent.h"
#include <GLM/glm.hpp>

class Transform2DComponent : public IActorComponent
{
public:
	static const ActorComponentId COMPONENT_ID = 2;

	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;

public:

	Transform2DComponent(const glm::vec2& position, const glm::vec2& size, 
		const float& rotation = 0)
		: m_position(position), m_size(size), m_rotation(rotation) {}

	Transform2DComponent(const float& x, const float& y, const float& width, 
		const float& height, const float& rotation = 0)
		: m_position(glm::vec2(x, y)), m_size(width, height), m_rotation(rotation) {}

	Transform2DComponent(const float& x, const float& y, const glm::vec2& size, 
		const float& rotation = 0)
		: m_position(glm::vec2(x, y)), m_size(size), m_rotation(rotation) {}

	Transform2DComponent(const glm::vec2& position, const float& width, 
		const float& height, const float& rotation = 0)
		: m_position(position), m_size(width, height), m_rotation(rotation) {}

	float GetDistance(const glm::vec2& otherPosition) const;
	void MoveBy(const float& x, const float& y);
	void MoveBy(const glm::vec2& distance);

	virtual ActorComponentId VGetComponentId() const override { return COMPONENT_ID; }
};
