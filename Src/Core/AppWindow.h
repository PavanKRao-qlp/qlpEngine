#pragma once
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include "Assert.h"

using namespace std;
class AppWindow
{
public:
	AppWindow(unsigned int width, unsigned int height);
	~AppWindow();
	bool Init();
	bool ShouldWindowClose();
	void RepaintWindow();
	void ClearWindow();
	unsigned int windowH, windowW;
private:
	GLFWwindow* mGlfwWindow;
};

