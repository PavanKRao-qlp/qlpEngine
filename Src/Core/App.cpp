#include "App.h"
#include <GLEW/glew.h> //needs to be first gl 
#include <GLFW/glfw3.h>

App::App()
{
}

App::~App()
{
}

bool App::Init()
{
	return CreateWindow();
	//Res loader Init
	//Sub system int 
	//GameLogic Init
}

bool App::CreateWindow()
{
	mWindow = make_unique<AppWindow>(1024, 720);
	return mWindow->Init();
}

void App::Run()
{
	mWindow->ClearWindow();
	while (!mWindow->ShouldWindowClose())
	{
		mWindow->ClearWindow();
		//Input
		//AI
		//PHY
		//STATE
		//GRAPH
		RenderUpdate();
		//AllProcees->update();
		//UpdateScengraph
		//Scene= 1
		mWindow->RepaintWindow();
	};
}

void App::Exit()
{
}
