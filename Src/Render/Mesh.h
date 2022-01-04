#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneNode.h"
#include "../Core/Graphics.h"
#include "../Render/Material.h"
#include <vector>
class Mesh : public IComponent
{
public:
    class Vertex
    {
    public:
        glm::vec3 V;
        glm::vec2 TexCord;
        glm::vec3 Normal;

        Vertex(glm::vec3 V_, glm::vec2 Tex , glm::vec3 Norm) {
            this->V = V_;
            this->TexCord = Tex;
            this->Normal = Norm;
        }
    };

    Mesh();
	~Mesh();
    virtual const char* GetComponentName() ;
    virtual void SetSceneNode(SceneNode* node);
    virtual SceneNode* GetSceneNode() ;
    void InitializeBuffer();

	void SubmitRender();
    std::vector<Vertex>* V;
    std::vector<glm::vec2>* TexCord;
    std::vector<unsigned int>* I;
    Material Mat;
private:
    unsigned int vbo_, vao_, ebo_;
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::mat4 model;
    float ts;
    SceneNode* sceneNode;

};
