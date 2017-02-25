#pragma once

#include "IActorComponent.h"

class SphereComponent : public IActorComponent
{
public:
	const static ActorComponentId COMPONENT_ID = 4;

	float m_radius;

public:
	SphereComponent(const float& radius = 5) : m_radius(5) {};
	~SphereComponent() = default;
};

