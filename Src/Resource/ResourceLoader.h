#pragma once
#include "../Core/Defination.h"
#include "../Core/MultiThreading.h"
#include <vector>
#include <map>
#include <thread>
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
	bool Load3DFileAsync(std::string path, std::function<void(SceneNode*)> callback);
	Shader* CurrShader;
private:

	std::unique_ptr<SimpleThreadPool> LoadWorker;
	//tasks
	SceneNode* Process3DSceneNode(aiNode* node, aiScene* scene , std::string path);
	Mesh* ProcessMesh(SceneNode* node, aiMesh* mesh3d, aiScene* scene , std::string path);
	void ProcessMaterial(aiMaterial* aiMat, Mesh* mesh, bool importTextures, std::string path);
	bool LoadTexureData(std::string path, Texture2D* texture2d);
	//async
	SceneNode* Process3DSceneNodeTask(aiNode* node, aiScene* scene, std::string path);
	float size;
	// ResourceMaps
	std::map<std::string, Texture2D*> TextureMap = {};
};
