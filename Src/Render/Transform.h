#pragma once
#include <glm/glm.hpp>
#include<glm/common.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
class Transform
{
public:
	Transform();
	~Transform();
	glm::mat4 GetMatrix();
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::quat RotationQ;
	glm::vec3 Scale;
private:
	glm::mat4 matrix;
};

