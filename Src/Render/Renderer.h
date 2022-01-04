#pragma once
#include <algorithm>
#include "SceneGraph.h"
class Renderer
{
public:
	Renderer();
	~Renderer();
	bool Init();
	void Update();
	void RenderGrapgh(SceneGraph* SG);
	void RenderNode(SceneNode* node);
private:
	SceneGraph* curSG;
	std::vector<Mesh*> rendGraph;
	bool IcompareCloserToCamera(Mesh* i, Mesh* j);
};

