#pragma once
#include <memory>
#include "Graphics.h"
#include "AppWindow.h"
#include "KeyboardInput.h"
#include "GameLogic.h"
#include "../Render/Renderer.h"
#include "../Hud.h"

using namespace std;
class App
{
public:
	App();
	~App();
	bool Init();
	void Run();
	void Exit();
	unique_ptr<AppWindow> mWindow;
	unique_ptr<GameLogic> mGameLogic;
	unique_ptr<Renderer> mRenderer;
	unique_ptr<KeyboardInput> mInput; //change to generic
	unique_ptr<Hud> mHud;
private:
	bool CreateWindow();
	
};
