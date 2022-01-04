#include "SceneNode.h"

SceneNode::SceneNode()
{
}

SceneNode::~SceneNode()
{
}

bool SceneNode::IsVisible()
{
	return Visible;
}

int SceneNode::GetPass()
{
	return 0;
}

std::vector<SceneNode*> SceneNode::GetChildren()
{
	return ChildObjects;
}

void SceneNode::AddChild(SceneNode* child)
{
	child->Parent = this;
	ChildObjects.push_back(child);
}

void SceneNode::AddComponent(IComponent* component)
{
	Components.push_back(component);
	component->SetSceneNode(this);
}

std::vector<IComponent*> SceneNode::GetComponents()
{
	return Components;
}

void SceneNode::RemoveChild(SceneNode child)
{
}

void SceneNode::SubmitRender()
{

}

glm::mat4 SceneNode::GetWorldTranform()
{
	if (Parent) {
		return Parent->GetWorldTranform() * LocalTranform.GetMatrix();
	}
	return  LocalTranform.GetMatrix();;
}
