#pragma once

#include <gl/glew.h>

class IShape
{
public:

	virtual GLuint VGetVao() const = 0;
};
