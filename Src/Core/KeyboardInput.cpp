#include "KeyboardInput.h"
KeyboardInput* instance;

KeyboardInput::KeyboardInput()
{
}

KeyboardInput::KeyboardInput(void* windowContext) : KeyState{}
{
	instance = this;
	window =  static_cast<GLFWwindow*>(windowContext);
	glfwSetKeyCallback(window, KeyboardCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetWindowFocusCallback(window, FocusCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

KeyboardInput::~KeyboardInput()
{
}

bool KeyboardInput::IsKeyDown(int keycode)
{
	if (KeyState && KeyState[keycode] == InputKeyState::KEY_HOLD) return true;
	return false;
}

bool KeyboardInput::IsKeyUp(int keycode)
{
	if (KeyState && KeyState[keycode] != InputKeyState::KEY_UP) return false;
	return true;
}

bool KeyboardInput::IsKeyPressed(int keycode) {
	if (window ) {
		//if (KeyState && KeyState[keycode] == InputKeyState::KEY_PRESS) return true;
		try
		{

			return(glfwGetKey(window, keycode) == GLFW_PRESS);
		}
		catch (const char* e)
		{
			return false;
		}
	}
	return false;
}

MousePos KeyboardInput::GetMousePos()
{
    return MousePos_;
}

 void KeyboardInput::ToggleMouse() {
	if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

 void KeyboardInput::FocusCallback(GLFWwindow* window, int focus)
 {
	 instance->focus = focus;
 }
 
 void KeyboardInput::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
 {
	 if (action == GLFW_RELEASE) {
		 instance->KeyState[key] = InputKeyState::KEY_UP;
	 }
	 else if (action == GLFW_PRESS)
	 {
		 instance->KeyState[key] = InputKeyState::KEY_PRESS;
	 }
	 else if (action == GLFW_REPEAT)
	 {
		 instance->KeyState[key] = InputKeyState::KEY_HOLD;
	 }
 }

void KeyboardInput::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	instance->MousePos_.X = xpos;
	instance->MousePos_.Y = ypos;
}


