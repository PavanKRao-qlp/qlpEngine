#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneNode.h"

class Camera : SceneNode
{
public:
	Camera();
	~Camera();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void SetProjection(float fov);
	void SetOrtho();
	void SetLookAt(glm::vec3 target);
	void SetPosition(glm::vec3 pos);
	void SetClipping(float near , float far);

	glm::vec3 Position;
	glm::vec3 Up; 
	glm::vec3 Forward;
private:
	glm::mat4 viewMX;
	glm::mat4 projMX;
	float near = 0.1f;
	float far = 10.0f;
};
