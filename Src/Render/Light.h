#pragma once
#include "../Core/IComponent.h"

class Light: public IComponent
{
public:
	Light();
	~Light();

	virtual const char* GetComponentName();
	virtual void SetSceneNode(SceneNode* node);
	virtual SceneNode* GetSceneNode();

	glm::vec3 Color;
	float Intensity;

private:
	SceneNode* sceneNode;

};
