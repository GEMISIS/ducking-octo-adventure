#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class camera
{
public:
	camera()
	{
	}
	camera(float fov, float aspectRatio)
	{
		this->rotation = glm::vec3(0, 0, 0);
		this->position = glm::vec3(0, 0, 0);

		this->perspectiveMatrix = glm::perspective(fov, aspectRatio, 0.001f, 10000.0f);
	}

	void StepForward(float amount)
	{
		this->Translate(
			amount * (cos(rotation.x / 180 * 3.14f) * sin(-rotation.y / 180 * 3.14f)),
			amount * (sin(rotation.x / 180 * 3.14f)),
			amount * (cos(rotation.x / 180 * 3.14f) * cos(-rotation.y / 180 * 3.14f)));
	}

	void Strife(float amount)
	{
		this->Translate(
			amount * sin(-rotation.y / 180 * 3.14f - (3.14f / 2.0f)), 
			0, 
			amount * cos(-rotation.y / 180 * 3.14f - (3.14f / 2.0f)));
	}

	void Translate(float x, float y, float z)
	{
		this->position += glm::vec3(x, y, z);
	}

	void Rotate(float x, float y, float z)
	{
		this->rotation += glm::vec3(x, y, z);
		this->direction = glm::vec3((cos(rotation.x / 180 * 3.14f) * sin(-rotation.y / 180 * 3.14f)),
			(sin(rotation.x / 180 * 3.14f)),
			(cos(rotation.x / 180 * 3.14f) * cos(-rotation.y / 180 * 3.14f)));
		this->right = glm::vec3(sin(-rotation.y / 180 * 3.14f - (3.14f / 2.0f)),
			0,
			cos(-rotation.y / 180 * 3.14f - (3.14f / 2.0f)));
		this->up = glm::cross(this->right, this->direction);
	}

	glm::mat4 GetPerspectiveMatrix()
	{
		return this->perspectiveMatrix;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->direction, this->up);
	}
private:
	glm::vec3 position, rotation, direction, up, right;
	glm::mat4 perspectiveMatrix;
};