#pragma once
#include <GLEW/glew.h> //needs to be first gl 
#include <glm\glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	unsigned int getUniformAddress(const char* uniformId) const;
	void Use();

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, const glm::vec2& value) const;

	void setVec2(const std::string& name, float x, float y) const;

	void setVec3(const std::string& name, const glm::vec3& value) const;

	void setVec3(const std::string& name, float x, float y, float z) const;

	void setVec4(const std::string& name, const glm::vec4& value) const;

	void setVec4(const std::string& name, float x, float y, float z, float w);

	void setMat2(const std::string& name, const glm::mat2& mat) const;

	void setMat3(const std::string& name, const glm::mat3& mat) const;

	void setMat4(const std::string& name, const glm::mat4& mat) const;

	void setBool(unsigned int id, bool value) const;

	void setInt(unsigned int id, int value) const;

	void setFloat(unsigned int id, float value) const;

	void setVec2(unsigned int id, const glm::vec2& value) const;

	void setVec2(unsigned int id, float x, float y) const;

	void setVec3(unsigned int id, const glm::vec3& value) const;

	void setVec3(unsigned int id, float x, float y, float z) const;

	void setVec4(unsigned int id, const glm::vec4& value) const;

	void setVec4(unsigned int id, float x, float y, float z, float w);

	void setMat2(unsigned int id, const glm::mat2& mat) const;

	void setMat3(unsigned int id, const glm::mat3& mat) const;

	void setMat4(unsigned int id, const glm::mat4& mat) const;

	void BindUniformBufferObject(const std::string& name, unsigned int bindIndex) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);

};

