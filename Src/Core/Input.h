#pragma once
#include <GLFW\glfw3.h>
class Input
{
public :
	Input();
	~Input();

	virtual bool IsKeyDown(int keycode);
	virtual bool IsKeyUp(int keycode);
	virtual bool IsKeyPressed(int keycode);
};

