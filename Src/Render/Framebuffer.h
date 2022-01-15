#include <vector>
#include "../Core/Graphics.h"
#include "Texture.h"
#pragma once
class Framebuffer {
public:
	Framebuffer(int width, int height, int noOfColorAttachment, bool depth, bool stencil);
	~Framebuffer();
	void ClearBuffer();
	int GetColorAttachment(int index);
	void StartWriting();
	void EndWriting();
	unsigned int ID;
	unsigned int texSize;
private:
	unsigned int rbo;
	std::vector<Texture2D*> colorAttachments;
};