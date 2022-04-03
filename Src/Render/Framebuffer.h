#include <vector>
#include "../Core/Graphics.h"
#include "Texture.h"
#pragma once
class Framebuffer {
public:
	Framebuffer(int width, int height, int noOfColorAttachment, bool depth, bool stencil);
	~Framebuffer();
	void ClearBuffer();
	void BlitToFrameBuffer(Framebuffer& destBuffer, GLbitfield blitMask, GLenum blitFilter = GL_NEAREST);
	void BlitFromFrameBuffer(Framebuffer& sourceBuffer, GLbitfield blitMask ,GLenum blitFilter);
	int GetColorAttachment(int index);
	void StartWriting();
	void StopWriting();
	unsigned int ID;
	unsigned int texSize;
	unsigned int Width, Height;
private:
	unsigned int rbo;
	std::vector<Texture2D*> colorAttachments;
};