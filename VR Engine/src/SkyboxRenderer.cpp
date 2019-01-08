#include "SkyboxRenderer.h"



SkyboxRenderer::SkyboxRenderer(Loader * loader)
	:m_Cube(loader->LoadToVAO(m_Vertices, 3)), m_Shader("res/shaders/Skybox.shader")
{
	m_TextureFiles = 
	{ 
		"res/textures/skybox/right.png", 
		"res/textures/skybox/left.png", 
		"res/textures/skybox/top.png", 
		"res/textures/skybox/bottom.png", 
		"res/textures/skybox/back.png", 
		"res/textures/skybox/front.png" 
	};
	m_TextureID = loader->LoadCubeMap(m_TextureFiles);
}


SkyboxRenderer::~SkyboxRenderer()
{
}

void SkyboxRenderer::Render(GameObject * cameraObject)
{
	m_Shader.Bind();
	m_Shader.LoadViewMatrix(cameraObject);
	glBindVertexArray(m_Cube.vaoID);
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 5);
	glDrawArrays(GL_TRIANGLES, 0, m_Cube.vertexCount);
	glBindVertexArray(0);
	m_Shader.Unbind();
}

void SkyboxRenderer::LoadProjectioMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}
