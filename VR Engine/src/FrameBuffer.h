#pragma once
#include <GL\glew.h>

#include "Window.h"
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void Unbind();
	GLuint GetTexture() { return m_TextureID; }

private:
	void CreateFrameBuffer();
	void CreateTextureAttachment(int width, int height);
	void CreateRenderBuffer(int width, int height);


private:
	GLuint m_RendererID;
	GLuint m_TextureID;
	GLuint m_RenderBufferID;
};

