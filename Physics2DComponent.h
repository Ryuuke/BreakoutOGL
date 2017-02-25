#pragma once

#include "IActorComponent.h"
#include <GLM/glm.hpp>

class Transform2DComponent;

class Physics2DComponent : public IActorComponent
{
public:
	const static ActorComponentId COMPONENT_ID = 3;

	glm::vec2 m_velocity;
public:
	Physics2DComponent(const glm::vec2& velocity = glm::vec2(200, -300)) : m_velocity(velocity) {}
	~Physics2DComponent() = default;

	virtual void VUpdate(const float& deltaTime, Transform2DComponent& transform);
	virtual ActorComponentId VGetComponentId() const override { return COMPONENT_ID; }
};
