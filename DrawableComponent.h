#pragma once
#include "IDrawableComponent.h"


class Transform2DComponent;

class DrawableComponent : public IDrawableComponent
{
public:
	using IDrawableComponent::IDrawableComponent;

	virtual void VDraw(const Transform2DComponent& transform) override;
};