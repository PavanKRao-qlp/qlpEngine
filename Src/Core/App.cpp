#include "App.h"

App::App()
{
}

App::~App()
{
}

bool App::Init()
{
	ASSERT_CORE_FATAL(CreateWindow(), "create window failed");
	mInput = make_unique<KeyboardInput>(mWindow->WindowPtr());
	mRenderer = make_unique<Renderer>();
	mGameLogic = make_unique<GameLogic>();
	mHud = make_unique<Hud>(mWindow->WindowPtr());
	//Res loader Init
	//Sub system int
	mGameLogic.get()->inputWeak =  (mInput.get());
	mHud.get()->SetSceneGrapgh(mGameLogic.get()->CurrScene.get());
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
		mGameLogic->Update();
		//Input
		//AI
		//PHY
		//STATE
		//GRAPH
		//AllProcees->update();
		//UpdateScengraph
		//Scene= 1
		mRenderer->RenderGrapgh(mGameLogic->CurrScene.get());
		mRenderer->Update();
		mHud->UpdateUI();
		mWindow->RepaintWindow();
	};
}


void App::Exit()
{
}
