#pragma once

#include "IShape.h"

class SquareShape : public IShape
{
private:
	GLuint m_squareVao = 0;
public:
	SquareShape() = default;
	~SquareShape() = default;

	void Init();
	void Destroy();

	GLuint VGetVao() const override { return m_squareVao; }
};

