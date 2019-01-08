#include "FrameBuffer.h"
#include "GL.h"



FrameBuffer::FrameBuffer()
{
	CreateFrameBuffer();
	CreateTextureAttachment(Window::Width,Window::Height);
	CreateRenderBuffer(Window::Width, Window::Height);
}


FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	//glViewport(0, 0, Window::Width,Window::Height);
}

void FrameBuffer::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	//glViewport(0, 0, Window::Width, Window::Height);
}

void FrameBuffer::CreateFrameBuffer()
{
	
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

 void FrameBuffer::CreateTextureAttachment(int width, int height)
{
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0));
}

 void FrameBuffer::CreateRenderBuffer(int width, int height)
 {
	 glGenRenderbuffers(1, &m_RenderBufferID);
	 glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
	 glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	 glBindRenderbuffer(GL_RENDERBUFFER, 0);
	 glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);
	 if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		 std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	 glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

