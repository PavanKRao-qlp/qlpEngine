#pragma once
#include "Render\SceneGraph.h"
#include "Render\Light.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
class Hud{
public:
	Hud(void* windowPtr);
	~Hud();
	void UpdateUI();
	void SetSceneGrapgh(SceneGraph* SG);
private:
	SceneGraph* sg_;
	void DrawHierarchyNode(SceneNode* node);
	void DrawnNodeInfo(SceneNode* node);
	void DrawComponent(IComponent* component);
	SceneNode* selectedNode = nullptr;
};