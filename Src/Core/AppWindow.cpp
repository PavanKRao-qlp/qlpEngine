#include "AppWindow.h"

AppWindow::AppWindow(unsigned int width, unsigned int height)
{
	windowH = height;
	windowW = width;
}

AppWindow::~AppWindow()
{
}

bool AppWindow::Init()
{
	ASSERT_CORE_FATAL(glfwInit(), "GLFW init failed");
	mGlfwWindow = glfwCreateWindow(windowW, windowH, "Engine", NULL, NULL);
	if(!mGlfwWindow){
		ASSERT_CORE_FATAL(mGlfwWindow, "GLFW Window create failed");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mGlfwWindow);
	ASSERT_CORE_FATAL(glewInit() == GLEW_OK, "GLEW OPENGL INIT FAILED"); // todo: move to grphics api ?
	return true;
}

bool AppWindow::ShouldWindowClose()
{
	if (mGlfwWindow) return glfwWindowShouldClose(mGlfwWindow);
	return false;
}

void AppWindow::RepaintWindow()
{
	glfwPollEvents();
	glfwSwapBuffers(mGlfwWindow);
}

void AppWindow::ClearWindow()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
