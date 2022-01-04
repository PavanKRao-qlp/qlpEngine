#include "Texture.h"

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}

void Texture2D::InitGLTextureData(unsigned char* data, int Width , int Height)
{
	if (data) {
		this->Width = Width;
		this->Height = Height;
		glGenTextures(1, &TexId);
		glBindTexture(GL_TEXTURE_2D, TexId);
		glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
