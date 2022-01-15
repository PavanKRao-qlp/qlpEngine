#pragma once
#include <memory>
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();
	void Update();
	void RenderGraph();
	void AddNode(SceneNode* node);
	std::vector<SceneNode*> RootObjects;
	Camera MainCamera;
private:
};