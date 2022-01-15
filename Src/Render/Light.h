#pragma once
#include "../Core/IComponent.h"

class Light: public IComponent
{
public:
	struct PointLightRendParams
	{
		glm::vec4 color;
		glm::vec4 position;
		glm::vec4  range;
	};

	Light();
	~Light();
	virtual const char* GetComponentName();
	virtual void SetSceneNode(SceneNode* node);
	virtual SceneNode* GetSceneNode();
	PointLightRendParams GetRendParams();
	glm::vec3 Color;
	float Intensity;

private:
	SceneNode* sceneNode;

};
