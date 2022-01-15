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

Light::PointLightRendParams Light::GetRendParams()
{
	Light::PointLightRendParams params;
	params.color = glm::vec4(Color, 1);
	params.position = sceneNode->GetWorldTranform()[3]; 
	params.range = glm::vec4(Color, 1);
	//params.range = 10;
	return params;
}
