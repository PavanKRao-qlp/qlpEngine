#include "Mesh.h"
Mesh::Mesh()
{
}

Mesh::~Mesh(){
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1, &vao_);
}

const char* Mesh::GetComponentName()  {
	return "MESH";
}

void Mesh::SetSceneNode(SceneNode* node)
{
	sceneNode = node;
}

SceneNode* Mesh::GetSceneNode()
{
	return sceneNode;
}

void Mesh::InitializeBuffer() {
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * V->size(), &V->front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * I->size(), &I->front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	if (Mat.Shader) {
		Mat.Shader->Use();
		Mat.Shader->BindUniformBufferObject("LightsBlock", 0);
	}
}

void Mesh::SubmitRender()
{
	if (sceneNode) {
		Mat.Shader->Use();
		model = sceneNode->GetWorldTranform();
		Mat.Shader->setMat4("u_M", model);
		if (Mat.DiffuseTex) 	Mat.Shader->setInt("u_diffuse", 0);
		if (Mat.NormalMapTex) 	Mat.Shader->setInt("u_normalMap", 1);
		Mat.Shader->setMat4("u_M", model);
		Mat.Shader->setVec3("u_ambientClr", Mat.AmbientColor);
		glActiveTexture(GL_TEXTURE0);
		if (Mat.DiffuseTex) glBindTexture(GL_TEXTURE_2D, Mat.DiffuseTex->TexId);
		glActiveTexture(GL_TEXTURE1);
		if (Mat.NormalMapTex) glBindTexture(GL_TEXTURE_2D, Mat.NormalMapTex->TexId);
	}
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES,I->size(), GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
