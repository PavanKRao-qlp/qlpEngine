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
	ASSERT_CORE_FATAL(CreateWindow(), "create window failed");
	//Res loader Init
	//Sub system int
	 return true;
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
		//AllProcees->update();
		//UpdateScengraph
		//Scene= 1
		mWindow->RepaintWindow();
	};
}

void App::Exit()
{
}
