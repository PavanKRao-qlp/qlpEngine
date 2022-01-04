#include "Camera.h"

Camera::Camera()
{
	Up = glm::vec3(0, 1, 0);
	Forward = glm::vec3(0, 0, -1);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMX;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projMX;
}

void Camera::SetProjection(float fov)
{
	projMX = glm::perspective(fov, 1024 / 720.0f, near, far);
}

void Camera::SetOrtho()
{
	projMX = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
}

void Camera::SetLookAt(glm::vec3 target)
{
	viewMX = glm::lookAt(Position, target, Position + Up);
}

void Camera::SetPosition(glm::vec3 pos)
{
	Position = pos; 
	viewMX = glm::lookAt(Position, Position + Forward ,  Up);
}

void Camera::SetClipping(float near, float far)
{
	this->near = near;
	this->far = far;
}
