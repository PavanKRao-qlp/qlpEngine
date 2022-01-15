#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "../Core/IComponent.h"
class IComponent;
class  SceneNode
{
public:
	 SceneNode();
	~ SceneNode();
	SceneNode(const SceneNode& refNode);
	bool IsVisible();
	int GetPass();
	std::vector<SceneNode*> GetChildren();
	std::vector<IComponent*> GetComponents();
	void AddChild(SceneNode* child);
	void AddComponent(IComponent* component);
	void RemoveChild(SceneNode child);
	virtual void SubmitRender();
	glm::mat4 GetWorldTranform();

	std::string Name;
	Transform LocalTranform;
	bool Visible = true;
private:
	std::vector<SceneNode*> ChildObjects;
	std::vector<IComponent*> Components;
	SceneNode* Parent;
};
