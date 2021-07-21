#pragma once
#include <memory>
#include "AppWindow.h"
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
};
