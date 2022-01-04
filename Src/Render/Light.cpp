#include "Light.h"

Light::Light() : Color(glm::vec3(1)), Intensity(1)
{
}

Light::~Light()
{
}

const char* Light::GetComponentName()
{
	return "PointLight";
}

void Light::SetSceneNode(SceneNode* node)
{
	sceneNode = node;
}

SceneNode* Light::GetSceneNode()
{
	return sceneNode;
}
