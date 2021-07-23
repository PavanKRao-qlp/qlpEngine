#pragma once
#include "../Core/Defination.h"

#ifdef  ASSIMP
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>
#endif //  ASSIMP

class  ResourceLoader
{
public:
	 ResourceLoader();
	~ ResourceLoader();
	bool Init();
	void Update();
	bool ParseShaderFile();

private:

};
