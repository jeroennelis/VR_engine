#include "PointCloudRenderer.h"



PointCloudRenderer::PointCloudRenderer()
	:m_Shader("res/shaders/PointCloud.shader")
{
}


PointCloudRenderer::~PointCloudRenderer()
{
}

void PointCloudRenderer::LoadProjectionMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}
void PointCloudRenderer::Render(Scene * scene, glm::mat4 & viewProjectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadUsingVR(scene->IsUsingVR());
	m_Shader.LoadViewMatrix(scene->GetCurrentCamera());
	Trans trans = Trans{ glm::vec3(0.0f,35.0f,-0.0f) ,270.0f,0.0f,0.0f,1.0f };
	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(trans);
	//glm::mat4 transformationMatrix = glm::mat4();
	m_Shader.LoadTransformationMatrix(transformationMatrix);
	for (RawModel model : *scene->GetPointCloud())
	{
		GLCall(glBindVertexArray(model.vaoID));
		m_Shader.LoadVRMatrix(viewProjectionMatrix);
		glDrawArrays(GL_POINTS, 0, model.vertexCount);
		GLCall(glBindVertexArray(0));
	}
	
	m_Shader.Unbind();
}
