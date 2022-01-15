#include "ResourceLoader.h"

#ifndef  STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // ! STB_IMAGE_IMPLEMENTATION

ResourceLoader::ResourceLoader()
{
}

ResourceLoader::~ResourceLoader()
{
}

bool ResourceLoader::Init()
{
	return true;
}

void ResourceLoader::Update()
{
}

bool ResourceLoader::ParseShaderFile()
{
	return false;
}

SceneNode* ResourceLoader::Load3DFile(std::string path)
{

	//make it async V imp
	Assimp::Importer importer3d;
	const aiScene* scene3D = importer3d.ReadFile(path,aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace |   aiProcess_GenUVCoords | aiProcess_GenSmoothNormals);
	if (scene3D) {
		auto* node = scene3D->mRootNode;
		path = path.substr(0,path.find_last_of('/')+1);
		return Process3DSceneNode(node, const_cast<aiScene*>(scene3D), path);
	}
	else
	{
		//todo assert
	}

	return nullptr;
}

SceneNode* ResourceLoader::Process3DSceneNode(aiNode* node ,aiScene* scene , std::string path) {
	SceneNode* Node_ = new SceneNode();
	Node_->Name = std::string(node->mName.C_Str());
	Node_->LocalTranform.Position =  *reinterpret_cast<glm::vec3*>(node->mTransformation[3]);
	if (node->mNumMeshes > 0)
	{
		for (auto msX = 0; msX < node->mNumMeshes; msX++) {
				auto childNode = ProcessMesh(Node_, scene->mMeshes[node->mMeshes[msX]], scene, path);
				Node_->AddComponent(childNode);
		}
	}
	if (node->mNumChildren > 0)
	{
		for (auto nx = 0; nx < node->mNumChildren; nx++) {
			auto childNode = Process3DSceneNode(node->mChildren[nx], scene, path);		
			Node_->AddChild(childNode);
		}
	}
	return Node_;
}

Mesh* ResourceLoader::ProcessMesh(SceneNode* node, aiMesh* mesh3d,  aiScene* scene , std::string path )
{
	/*aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	for (auto p = 0; p < material->mNumProperties; p++) {
		auto prop = material->mProperties[p];
		int i = 0;
	}*/
	//auto material = ;

	int vNum = mesh3d->mNumVertices;
	int iNum = mesh3d->mNumFaces * 3;

	Mesh* mesh_ = new Mesh();
	mesh_->V = new std::vector<Mesh::Vertex>();
	mesh_->I = new std::vector<unsigned int>();
	mesh_->V-> reserve(vNum); 
	mesh_->I-> reserve(iNum); 

	if (mesh3d->HasTextureCoords(0)) {
		mesh_->TexCord = new std::vector<glm::vec2>();
	}
	for (auto v = 0; v < vNum; v++)
	{
		//mesh_->V->push_back(Mesh::Vertex((*reinterpret_cast<glm::vec3*>(&mesh3d->mVertices[v])), (*reinterpret_cast<glm::vec2*>(&mesh3d->mTextureCoords[0][v])) ));
		if (mesh3d->HasTextureCoords(0) && mesh3d->HasNormals()) {
			mesh_->V->push_back(Mesh::Vertex( 
				(*reinterpret_cast<glm::vec3*>(&mesh3d->mVertices[v])),
				(*reinterpret_cast<glm::vec2*>(&mesh3d->mTextureCoords[0][v])),
				(*reinterpret_cast<glm::vec3*>(&mesh3d->mNormals[v]))));	
			  //	mesh_->TexCord->push_back(*reinterpret_cast<glm::vec2*>(&mesh3d->mTextureCoords[0][v]));
		}
		else {
			mesh_->V->push_back(Mesh::Vertex((*reinterpret_cast<glm::vec3*>(&mesh3d->mVertices[v])), glm::vec2(0,0), (*reinterpret_cast<glm::vec3*>(&mesh3d->mNormals[v]))));
		}
	}

	for (auto v = 0; v < mesh3d->mNumFaces; v++)
	{
		unsigned int vertexIndex = mesh3d->mFaces[v].mIndices[0];
		mesh_->I->push_back(vertexIndex);
		vertexIndex = mesh3d->mFaces[v].mIndices[1];
		mesh_->I->push_back(vertexIndex);
		vertexIndex = mesh3d->mFaces[v].mIndices[2];
		mesh_->I->push_back(vertexIndex);
	}

	ProcessMaterial(scene->mMaterials[mesh3d->mMaterialIndex], mesh_, true, path);
	mesh_->InitializeBuffer();
	return mesh_;
}

void ResourceLoader::ProcessMaterial(aiMaterial* aiMat , Mesh* mesh, bool importTextures , std::string path)
{
	aiString matName = aiMat->GetName();
	mesh->Mat.Name = matName.C_Str();
	aiString matDiffuse;
	aiMat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), matDiffuse);
	mesh->Mat.DiffuseTexPath = matDiffuse.C_Str();
	if (importTextures) {
		//path + mesh->Mat.DiffuseTexPath
		if (TextureMap.count(path + mesh->Mat.DiffuseTexPath) == 0) {
			mesh->Mat.DiffuseTex = new Texture2D();
			LoadTexureData(path + mesh->Mat.DiffuseTexPath, mesh->Mat.DiffuseTex);
			TextureMap.emplace(path + mesh->Mat.DiffuseTexPath, mesh->Mat.DiffuseTex);
		}
		else
		{
			mesh->Mat.DiffuseTex = TextureMap[path + mesh->Mat.DiffuseTexPath];
		}
	}
	mesh->Mat.Shader = CurrShader;
}

bool ResourceLoader::LoadTexureData(std::string path, Texture2D* texture2d)
{
	int w, h , c = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* texData = stbi_load(path.c_str(), &w, &h, &c, 4);
		if (!texData)
		{
			//todo alert tex importFail
			return false;
		}
		texture2d->InitGLTextureData(texData, w, h);
		stbi_image_free(texData);
	return true;
}


