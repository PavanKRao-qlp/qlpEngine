#pragma once
#include "Graphics.h"
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
	inline void* WindowPtr() { return mGlfwWindow; }
private:
	GLFWwindow* mGlfwWindow;
};

