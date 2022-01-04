#pragma once
#include "../Core/Defination.h"
#include <vector>
#include <map>
//
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>
//
#include "../Render/Shader.h"
#include "../Render/Mesh.h"
#include "../Render/Texture.h"

class  ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	bool Init();
	void Update();
	bool ParseShaderFile();
	SceneNode* Load3DFile(std::string path);
	Shader* CurrShader;
private:
	SceneNode* Process3DSceneNode(aiNode* node, aiScene* scene , std::string path);
	Mesh* ProcessMesh(SceneNode* node, aiMesh* mesh3d, aiScene* scene , std::string path);
	void ProcessMaterial(aiMaterial* aiMat, Mesh* mesh, bool importTextures, std::string path);
	bool LoadTexureData(std::string path, Texture2D* texture2d);
	std::map<std::string, Texture2D*> TextureMap = {};
	float size;
	//impt todo res map and res unload
};
