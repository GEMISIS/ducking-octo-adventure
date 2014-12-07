#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "shader_program.h"

float deltaTime = 0;

enum class STATE_ERRORS
{
	NONE = 0,
	NOT_OVERWRITTEN = -1,
	INIT_ERROR = -2
};

class tiny_state
{
public:
	virtual STATE_ERRORS Initialize(GLFWwindow* window)
	{
		return STATE_ERRORS::NOT_OVERWRITTEN;
	}
	virtual void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
	}
	virtual STATE_ERRORS Update(GLFWwindow* window)
	{
		return STATE_ERRORS::NOT_OVERWRITTEN;
	}
	virtual STATE_ERRORS Render(GLFWwindow* window)
	{
		return STATE_ERRORS::NOT_OVERWRITTEN;
	}
	virtual STATE_ERRORS Destroy()
	{
		return STATE_ERRORS::NOT_OVERWRITTEN;
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

	STATE_ERRORS setState(tiny_state* nextState)
	{
		STATE_ERRORS status = STATE_ERRORS::NONE;
		if (this->tinyState != nullptr)
		{
			status = this->tinyState->Destroy();
		}

		if (status != STATE_ERRORS::NONE)
		{
			return status;
		}

		this->tinyState = nextState;

		if (this->tinyState != nullptr)
		{
			glfwSetKeyCallback(this->window, __stateUseKeyCallback);
			status = this->tinyState->Initialize(this->window);
		}
		return status;
	}

	STATE_ERRORS Update()
	{
		deltaTime = float(currentTime - lastTime);
		this->currentTime = glfwGetTime();
		glfwPollEvents();
		return this->tinyState->Update(this->window);
	}

	STATE_ERRORS Render()
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
