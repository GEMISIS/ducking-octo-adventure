#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

#include "game_state.h"

#include "test_state.h"

#ifdef _DEBUG
void errorCallback(int error, const char* errorDescription)
{
	std::cout << "Error";
}
#endif


#ifdef _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	if (!glfwInit())
	{
		exit(0);
	}

#ifdef _DEBUG
	glfwSetErrorCallback(errorCallback);
	mainState.createWindow(640, 480, "ducking-octo-adventure", false);
#else
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	mainState.createWindow(mode->width, mode->height, "ducking-octo-adventure", true);
#endif

	if (glewInit() != GLEW_OK)
	{
		exit(0);
	}

	int version[2];
	glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
	glGetIntegerv(GL_MINOR_VERSION, &version[1]);
	std::cout << "OpenGL Version: " << version[0] << "." << version[1];

	mainState.setState(new test_state());
	while (!glfwWindowShouldClose(mainState.window))
	{
		mainState.Update();
		mainState.Render();
	}

	glfwTerminate();
	return 0;
}