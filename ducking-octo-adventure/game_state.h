#pragma once

#include <GLFW/glfw3.h>

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

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

class game_state
{
public:
	game_state()
	{
	}
	game_state(game_state const&);
	void operator=(game_state const&);

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
			glfwSetKeyCallback(this->window, keyCallback);
			status = this->tinyState->Initialize();
		}
		return status;
	}

	int Update()
	{
		return this->tinyState->Update(this->window);
	}

	int Render()
	{
		return this->tinyState->Render(this->window);
	}

	GLFWwindow* window;
private:
	tiny_state* tinyState;
};

static game_state mainState;

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	mainState.tinyKeyCallback(window, key, scanCode, action, mods);
}
