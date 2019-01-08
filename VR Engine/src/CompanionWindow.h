#pragma once
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <openvr.h>
#include "Window.h"


struct Framebuffer
{
	GLuint m_nDepthBufferId;
	GLuint m_nRenderTextureId;
	GLuint m_nRenderFramebufferId;
	GLuint m_nResolveTextureId;
	GLuint m_nResolveFramebufferId;
};

struct VertexDataWindow
{
	glm::vec2 position;
	glm::vec2 texCoord;

	VertexDataWindow(const glm::vec2 & pos, const glm::vec2 tex) : position(pos), texCoord(tex) {	}
};

class CompanionWindow
{
public:
	CompanionWindow(vr::IVRSystem &VRSettings);
	~CompanionWindow();
	bool SetupStereoRenderTargets(vr::IVRSystem &VRSettings);
	bool CreateFrameBuffer(int nWidth, int nHeight, Framebuffer & framebufferDesc);
	void SetupCompanionWindow();

	GLuint getVAO() { return m_VAO; }
	unsigned int getIndexSize() { return m_indexSize; }
	
	Framebuffer & getLeftEyeFrameBuffer() { return m_leftEyeFrameBuffer; }
	Framebuffer & getRightEyeFrameBuffer() { return m_rightEyeFrameBuffer; }

	uint32_t getRenderWidth() { return m_renderWidth; }
	uint32_t getRenderHeight() { return m_renderHeight; }


private:
	uint32_t m_renderWidth;
	uint32_t m_renderHeight;

	Framebuffer m_leftEyeFrameBuffer;
	Framebuffer m_rightEyeFrameBuffer;

	unsigned int m_indexSize;
	GLuint m_VAO;
	GLuint m_vertBuffer;
	GLuint m_indexBuffer;
};

