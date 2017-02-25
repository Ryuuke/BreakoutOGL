#include "Physics2DComponent.h"
#include "Actor.h"
#include "Transform2DComponent.h"

void Physics2DComponent::VUpdate(const float& deltaTime, Transform2DComponent& transform)
{
	transform.MoveBy(m_velocity * deltaTime);
}