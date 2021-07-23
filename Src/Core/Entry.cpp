#pragma once
#include "App.h"
#include "Assert.h"

#define ASSIMP

int main() {

	App app;
	ASSERT_CORE_FATAL(app.Init(), "Init Failed");
	app.Run();
	//Run App
	app.Exit();
	//Kill App
}