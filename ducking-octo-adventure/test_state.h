#pragma once

#include "game_state.h"
#include "camera.h"

class test_state : public tiny_state
{
private:
	shader_program shader;
	camera cam;

	int windowX, windowY, windowWidth, windowHeight;
	double mouseX, mouseY;
public:
	test_state()
	{
	}
	STATE_ERRORS Initialize(GLFWwindow* window)
	{
		shader = shader_program("test.vert", "test.frag");
		cam = camera(45.0f, 640.0f / 480.0f);
		cam.Translate(0, 0, -2.0f);

		glfwGetCursorPos(window, &this->mouseX, &this->mouseY);
		glfwGetWindowPos(window, &this->windowX, &this->windowY);
		glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);
		glfwSetCursorPos(window, this->windowX + (this->windowWidth / 2), this->windowY + (this->windowHeight / 2));

		if (shader.Use() != SHADER_ERRORS::NONE)
		{
			return STATE_ERRORS::INIT_ERROR;
		}
		return STATE_ERRORS::NONE;
	}
	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
	STATE_ERRORS Update(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) & GLFW_PRESS)
		{
			cam.Rotate(0, -0.01f, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) & GLFW_PRESS)
		{
			cam.Rotate(0, 0.01f, 0);
		}

		glfwGetCursorPos(window, &this->mouseX, &this->mouseY);

		glfwGetWindowPos(window, &this->windowX, &this->windowY);
		glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);

		glfwSetCursorPos(window, this->windowX + (this->windowWidth / 2), this->windowY + (this->windowHeight / 2));

		cam.Rotate(0, -(float(this->windowX + (this->windowWidth / 2)) - (float)this->mouseX), 0);
		cam.Rotate((float(this->windowY + (this->windowHeight / 2)) - (float)this->mouseY), 0, 0);
		/*
		if (glfwGetKey(window, GLFW_KEY_UP) & GLFW_PRESS)
		{
			cam.Rotate(-0.01f, 1, 0, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) & GLFW_PRESS)
		{
			cam.Rotate(0.01f, 1, 0, 0);
		}
		*/
		if (glfwGetKey(window, GLFW_KEY_W) & GLFW_PRESS)
		{
			cam.StepForward(0.001f);
		}
		if (glfwGetKey(window, GLFW_KEY_S) & GLFW_PRESS)
		{
			cam.StepForward(-0.001f);
		}
		if (glfwGetKey(window, GLFW_KEY_A) & GLFW_PRESS)
		{
			cam.Strife(-0.001f);
		}
		if (glfwGetKey(window, GLFW_KEY_D) & GLFW_PRESS)
		{
			cam.Strife(0.001f);
		}
		return STATE_ERRORS::NONE;
	}
	STATE_ERRORS Render(GLFWwindow* window)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->shader.Use();
		this->shader.SetUniform("perspectiveMatrix", this->cam.GetPerspectiveMatrix());
		this->shader.SetUniform("viewMatrix", this->cam.GetViewMatrix());

		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		return STATE_ERRORS::NONE;
	}
	STATE_ERRORS Destroy()
	{
		return STATE_ERRORS::NONE;
	}
};