#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

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
#endif

	glfwTerminate();
	return 0;
}