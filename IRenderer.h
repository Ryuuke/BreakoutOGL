#pragma once

#include "GLM/glm.hpp"

class Texture;

struct IRenderer
{
	virtual void VDraw(const Texture* const texture, const glm::vec2& position,
		const glm::vec2& size, const float& rotation,
		const glm::vec3& color) const = 0;
};

