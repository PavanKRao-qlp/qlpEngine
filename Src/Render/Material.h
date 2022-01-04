#pragma once
#include <glm\glm.hpp>
#include <string>
#include "Texture.h"
#include "../Render/Shader.h"
class Material
{
public:
	const char* Name;
	glm::vec3 AmbientColor = glm::vec3(1);
	glm::vec3 DiffuseColor;
	glm::vec3 SpecularColor;
	const char* DiffuseTexPath;
	Texture2D* DiffuseTex;
	Shader* Shader;
};

