#pragma once
#include<memory>
#include "../Render/Mesh.h"
#include "../Render/Light.h"
#include "../Render/SceneGraph.h"
#include "../Render/Camera.h"
#include "../Render/Shader.h"
#include "../Resource/ResourceLoader.h"
#include "../Core/KeyboardInput.h"
#include "../../DummyCube.h"	
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void Update();
	std::unique_ptr<SceneGraph> CurrScene;
	KeyboardInput* inputWeak; // change
private:
	void On3DObjectLoaded(SceneNode* node);
	std::unique_ptr<DummyCube> cube;
	std::unique_ptr<Light> light;
	std::unique_ptr<Light> light2;
	Camera* mainCam;
	Shader* TempColor; //change
	bool firstMouse = true;
	float lastX, lastY , yaw , pitch;
	bool takeMouseInput = true;
	std::unique_ptr<ResourceLoader> ResLoaderUPtr;
};
