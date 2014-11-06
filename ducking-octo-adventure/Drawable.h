#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "stb_image.h"
#include "shader_program.h"

typedef enum DRAWABLE_ERRORS
{
	NONE = 0,
	NOT_OVERWRITTEN = -1
};

class Drawable
{
public:
	virtual DRAWABLE_ERRORS Load(shader_program* shader)
	{
		this->shader = shader;
		return NOT_OVERWRITTEN;
	}
	virtual DRAWABLE_ERRORS Load(shader_program* shader, const char* filename)
	{
		this->shader = shader;
		return NOT_OVERWRITTEN;
	}
	virtual DRAWABLE_ERRORS Render()
	{
		return NOT_OVERWRITTEN;
	}
	virtual DRAWABLE_ERRORS Destroy()
	{
		return NOT_OVERWRITTEN;
	}
private:
	shader_program* shader;
};