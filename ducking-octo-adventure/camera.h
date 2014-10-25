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
		this->rotationVec = glm::vec3(0, 0, 0);

		this->position = glm::mat4(1.0f);
		this->rotation = glm::mat4(1.0f);

		this->perspectiveMatrix = glm::perspective(fov, aspectRatio, 0.001f, 10000.0f);
	}

	void StepForward(float amount)
	{
		this->Translate(
			amount * (cos(rotationVec.x / 180 * 3.14f) * sin(-rotationVec.y / 180 * 3.14f)),
			amount * (sin(rotationVec.x / 180 * 3.14f)),
			amount * (cos(rotationVec.x / 180 * 3.14f) * cos(-rotationVec.y / 180 * 3.14f)));
	}

	void Strife(float amount)
	{
		this->Translate(
			amount * sin(-rotationVec.y / 180 * 3.14f - (3.14f / 2.0f)), 
			0, 
			amount * cos(-rotationVec.y / 180 * 3.14f - (3.14f / 2.0f)));
	}

	void Translate(float x, float y, float z)
	{
		this->position = glm::translate(this->position, glm::vec3(x, y, z));
	}

	void Rotate(float angle, float x, float y, float z)
	{
		this->rotation = glm::rotate(this->rotation, angle, glm::vec3(x, y, z));
		rotationVec += glm::vec3(x * angle, y * angle, z * angle);
	}

	glm::mat4 GetPerspectiveMatrix()
	{
		return this->perspectiveMatrix;
	}

	glm::mat4 GetViewMatrix()
	{
		return this->rotation * this->position;
	}
private:
	glm::vec3 rotationVec;
	glm::mat4 position, rotation;
	glm::mat4 perspectiveMatrix;
};