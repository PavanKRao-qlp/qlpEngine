#include "Framebuffer.h"

Framebuffer::Framebuffer(int width , int height , int noOfColorAttachment = 1, bool depth = true ,  bool stencil = true)
{
	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	if(noOfColorAttachment > 15){
	 //todo error 
		noOfColorAttachment = 15;
	}
	texSize = noOfColorAttachment;

	GLenum* attachmentsIndex = new GLenum[noOfColorAttachment];
	for (int i = 0; i < noOfColorAttachment; i++)
	{
		Texture2D* tex = new Texture2D();
		tex->InitGLTextureData(nullptr, width, height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0+i), GL_TEXTURE_2D, tex->TexId, 0);
		colorAttachments.push_back(tex);
		attachmentsIndex[i] = GL_COLOR_ATTACHMENT0 + i;
	};

	glDrawBuffers(noOfColorAttachment, attachmentsIndex);
	if (stencil || depth) {
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		GLenum attachmentType, internalFormat = 0;
		if (depth && stencil) {
			internalFormat = GL_DEPTH24_STENCIL8;
			attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
		}
		else if (depth && !stencil) {
			internalFormat = GL_DEPTH;
			attachmentType = GL_DEPTH_ATTACHMENT;
		}
		else if (stencil && !depth) {
			internalFormat = GL_STENCIL;
			attachmentType = GL_STENCIL_ATTACHMENT;
		}

		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, rbo);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		//todo error
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
	//todo delete textures
}

void Framebuffer::ClearBuffer()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

int Framebuffer::GetColorAttachment(int index) {
	return colorAttachments[index]->TexId;
}

void Framebuffer::StartWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void Framebuffer::EndWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
