#include "GrassRenderer.h"



GrassRenderer::GrassRenderer()
	:m_Shader("res/shaders/Grass.shader")
{
}


GrassRenderer::~GrassRenderer()
{
}

void GrassRenderer::LoadProjectionMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}

void GrassRenderer::Render(Scene * scene, const glm::mat4 & viewProjectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadViewMatrix(scene->GetCurrentCamera());
	Trans trans = Trans{ glm::vec3(0.0f,35.0f,-0.0f) ,270.0f,0.0f,0.0f,1.0f };
	glm::mat4 transformationMatrix = glm::mat4();
	m_Shader.LoadTransformationMatrix(transformationMatrix);
	for (RawModel model : *scene->GetGrass())
	{
		GLCall(glBindVertexArray(model.vaoID));
		glDrawArrays(GL_POINTS, 0, model.vertexCount);
		GLCall(glBindVertexArray(0));
	}




	m_Shader.Unbind();
}
