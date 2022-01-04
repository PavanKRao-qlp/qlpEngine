#pragma once
#include "../Core/Graphics.h"
class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	void InitGLTextureData(unsigned char* data, int Width, int Height);
	unsigned int TexId = 0;
	unsigned int Width = 0;
	unsigned int Height = 0;
private:

};
