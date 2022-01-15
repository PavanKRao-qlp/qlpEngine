#pragma once
#include <algorithm>
#include "SceneGraph.h"
#include "Framebuffer.h"
class Renderer
{
public:
	Renderer();
	~Renderer();
	bool Init();
	void Update();
	void RenderGrapgh(SceneGraph* SG);
	void RenderNode(SceneNode* node);

	std::unique_ptr<Framebuffer> frameBuffer_clr; //todo move to priv
private:
	SceneGraph* curSG;
	std::vector<Mesh*> activeMesh;
	std::vector<Light*> activeLight;
	std::unique_ptr<Mesh> DrawQuad1;
	std::unique_ptr<Shader> RenderViewShader;
	bool IcompareCloserToCamera(Mesh* i, Mesh* j);
	unsigned int lightsUBO;
	glm::vec4 clr = glm::vec4(1,0,0,1);
	void DoTestPass();
};

