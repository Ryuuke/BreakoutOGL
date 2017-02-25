#pragma once

#include "Shader.h"
#include "Texture.h"
#include "IRenderer.h"

class SpriteRenderer : public IRenderer
{
private:
	Shader* m_shader;
	GLuint m_quadVao = 0;
public:
	SpriteRenderer(Shader* const shader) : m_shader(shader){}
	~SpriteRenderer() = default;

	void Init();
	void Destroy();
	virtual void VDraw(const Texture* const texture, const glm::vec2& position,
		const glm::vec2& size = glm::vec2(10, 10), const float& rotation = 0.f,
		const glm::vec3& color = glm::vec3(1.0)) const override;
};