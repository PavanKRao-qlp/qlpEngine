#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	for (auto node : RootObjects) {
		delete node;
	}
	RootObjects.clear();
}

void SceneGraph::Update()
{
}

void SceneGraph::RenderGraph()
{
	/*for (SceneNode node : RootObjects) {
		if (node.IsVisible()) {
			if (node.GetPass() == 0) {
				node.SubmitRender();
			}
		}
	}*/
}

void SceneGraph::AddNode(SceneNode* node)
{
	RootObjects.push_back(node);
}
