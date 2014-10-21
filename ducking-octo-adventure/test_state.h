#pragma once

#include "game_state.h"

class test_state : public tiny_state
{
private:
	shader_program shader;
public:
	int Initialize()
	{
		shader = shader_program("test.vert", "test.frag");
		return shader.Use();
	}
	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
	int Update(GLFWwindow* window)
	{
		return 1;
	}
	int Render(GLFWwindow* window)
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();
		return 1;
	}
	int Destroy()
	{
		return 1;
	}
};