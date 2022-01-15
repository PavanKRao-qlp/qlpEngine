#include "DummyCube.h"
#include "Src\Resource\stb_image.h"

DummyCube::DummyCube()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
   
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("Assets/3D/Gene/Tex_0657_0.png", &width, &height, &nrChannels,4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    Mat = new Material();
}

void DummyCube::SubmitRender()
{
    Mat->Shader->setInt("u_diffuse", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    Mat->Shader->setMat4("u_M",node->GetWorldTranform());
    //if (Mat.DiffuseTex) 	Mat.Shader->setInt("u_diffuse", 0);
    //Mat.Shader->setVec3("u_ambientClr", Mat.AmbientColor);
    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

const char* DummyCube::GetComponentName()
{
    return "fakeCube";
}

void DummyCube::SetSceneNode(SceneNode* node)
{
    this->node = node;
}

SceneNode* DummyCube::GetSceneNode()
{
    return node;
}
