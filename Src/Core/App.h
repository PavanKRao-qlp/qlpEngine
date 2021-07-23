#pragma once
#include <memory>
#include "AppWindow.h"
#include "../Render/Renderer.h"
using namespace std;
class App
{
public:
	App();
	~App();
	bool Init();
	void Run();
	void Exit();
private:
	bool CreateWindow();
	unique_ptr<AppWindow> mWindow;
	unique_ptr<Renderer> mRenderer;
};
