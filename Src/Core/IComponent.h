#pragma once
#include "../Render/SceneNode.h"
class SceneNode;
class IComponent
{
public:

	virtual const char* GetComponentName() = 0;
	virtual void SetSceneNode(SceneNode* node) = 0;
	virtual SceneNode* GetSceneNode() = 0;

private:

};