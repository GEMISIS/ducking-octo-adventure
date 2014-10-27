#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "shader_program.h"

float deltaTime = 0;

class tiny_state
{
public:
	virtual int Initialize()
	{
		return 0;
	}
	virtual void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
	}
	virtual int Update(GLFWwindow* window)
	{
		return 0;
	}
	virtual int Render(GLFWwindow* window)
	{
		return 0;
	}
	virtual int Destroy()
	{
		return 0;
	}
};

static void __stateUseKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

class game_state
{
public:
	game_state()
	{
	}
	game_state(game_state const&);
	void operator=(game_state const&);
	~game_state()
	{
		if (this->tinyState != nullptr)
		{
			this->tinyState->Destroy();
		}
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	bool createWindow(int width, int height, const char* title, bool fullScreen)
	{
		if (this->window)
		{
			glfwDestroyWindow(this->window);
		}
		this->window = glfwCreateWindow(width, height, title, (fullScreen) ? glfwGetPrimaryMonitor() : NULL, NULL);
		if (this->window != NULL)
		{
			glfwMakeContextCurrent(this->window);
		}
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		return this->window != NULL;
	}

	void tinyKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		this->tinyState->keyCallback(window, key, scanCode, action, mods);
	}

	int setState(tiny_state* nextState)
	{
		int status = 1;
		if (this->tinyState != nullptr)
		{
			status = this->tinyState->Destroy();
		}

		if (status != 1)
		{
			return status;
		}

		this->tinyState = nextState;

		if (this->tinyState != nullptr)
		{
			glfwSetKeyCallback(this->window, __stateUseKeyCallback);
			status = this->tinyState->Initialize();
		}
		return status;
	}

	int Update()
	{
		deltaTime = float(currentTime - lastTime);
		this->currentTime = glfwGetTime();
		glfwPollEvents();
		return this->tinyState->Update(this->window);
	}

	int Render()
	{
		glfwSwapBuffers(this->window);
		return this->tinyState->Render(this->window);
	}

	GLFWwindow* window;
private:
	tiny_state* tinyState;
	double currentTime, lastTime;
};

static game_state mainState;

static void __stateUseKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	mainState.tinyKeyCallback(window, key, scanCode, action, mods);
}
