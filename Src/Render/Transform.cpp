#include "Transform.h"

Transform::Transform() : 
	Position(glm::vec3(0)),
	Rotation(glm::vec3(0)),
	Scale(glm::vec3(1)),
	RotationQ(glm::quat(Rotation)),
	matrix(glm::mat4(1))
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix()
{
	RotationQ = glm::quat(glm::vec3(glm::radians(Rotation.x), glm::radians(Rotation.y),glm::radians(Rotation.z)));
	matrix = glm::translate(glm::mat4(1), Position) * glm::toMat4(RotationQ) * glm::scale(glm::mat4(1), Scale);
	return matrix;
}
