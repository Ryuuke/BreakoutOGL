#pragma once

#include "IActorComponent.h"
#include <GLM/glm.hpp>

class Texture;
class Shader;
class IShape;
class Transform2DComponent;

class IDrawableComponent : public IActorComponent
{
public:
	const static ActorComponentId COMPONENT_ID = 1;

	Texture* m_texture;
	Shader* m_shader;
	IShape* m_shape;
	glm::vec3 m_color;
	bool m_bIsVisible = true;

public:
	IDrawableComponent(Texture* const texture, Shader* const shader, IShape* const shape, const glm::vec3& color = glm::vec3(1.f, 1.f, 1.f));
	
	virtual void VDraw(const Transform2DComponent& transform) = 0;

	virtual ActorComponentId VGetComponentId() const override { return COMPONENT_ID; }
};
