#pragma once
#include "GL.h"
#include "Window.h"

class WaterFrameBuffers
{
public:
	WaterFrameBuffers();
	~WaterFrameBuffers();

	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();
	void UnbindCurrentFrameBuffer();

	inline GLuint GetReflectionTexture() { return reflectionTexture; }
	inline GLuint GetRefractionTexture() { return refractionTexture; }
	inline GLuint GetRefractionDepthTexture() { return refractionDepthTexture; }
	
private:
	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;

	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	void InitializeReflectionFrameBuffer();
	void InitializeRefractionFrameBuffer();

	void BindFrameBuffer(GLuint frameBuffer, int width, int height);
	GLuint CreateFrameBuffer();
	GLuint CreateTextureAttachment(int width, int height);
	GLuint CreateDepthTextureAttachment(int width, int height);
	GLuint CreateDepthBufferAttachment(int width, int height);

};

