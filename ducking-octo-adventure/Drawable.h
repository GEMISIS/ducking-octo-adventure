#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "stb_image.h"

typedef enum DRAWABLE_ERRORS
{
	NONE = 0,
	NOT_OVERWRITTEN = -1
};

class Drawable
{
public:
	virtual DRAWABLE_ERRORS Render()
	{
		return NOT_OVERWRITTEN;
	}
private:
};