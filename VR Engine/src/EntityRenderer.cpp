#include "EntityRenderer.h"
#include "MasterRenderer.h"


EntityRenderer::EntityRenderer()
	:m_Shader("res/shaders/Basic.shader")
{
}

EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::LoadProjectionMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}

void EntityRenderer::Render(Scene * scene, const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane)
{
	m_Shader.Bind();
	m_Shader.LoadClipPlane(clipPlane);
	m_Shader.LoadUsingVR(scene->IsUsingVR());
	m_Shader.loadLight(scene->GetLight());
	m_Shader.LoadViewMatrix(scene->GetCurrentCamera());
	m_Shader.LoadSkyColour(MasterRenderer::RED, MasterRenderer::GREEN, MasterRenderer::BLUE);
	
	std::unordered_map <GLuint, std::vector<Entity*>> * entities = scene->GetStaticEntities();
	for (auto it = entities->begin(); it != entities->end(); it++)
	{
		TexturedModel * model = it->second[0]->GetModel();
		PrepareTexturedModel(model);
		std::vector <Entity*> batch = it->second;
		for (Entity * entity : batch)
		{
			PrepareInstance(entity);
			m_Shader.LoadVRMatrix(viewProjectionMatrix);
			glDrawElements(GL_TRIANGLES, model->GetRawModel()->vertexCount, GL_UNSIGNED_INT, 0);
		}
		UnbindTexturedModel();
	}

	for (GameObject *gameObject : *scene->getGameObjects())
	{
		MeshRenderer *renderer = gameObject->GetComponent<MeshRenderer>();
		if (renderer != NULL)
		{
			TexturedModel * model = renderer->GetModel();
			PrepareTexturedModel(model);
			glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(gameObject->GetComponent<Transform>());
			m_Shader.LoadTransformationMatrix(transformationMatrix);
			m_Shader.LoadVRMatrix(viewProjectionMatrix);
			glDrawElements(GL_TRIANGLES, model->GetRawModel()->vertexCount, GL_UNSIGNED_INT, 0);
		}
	}

	m_Shader.Unbind();
}

void EntityRenderer::PrepareTexturedModel ( TexturedModel * texturedModel)
{
	
	RawModel* model = texturedModel->GetRawModel();
	GLCall(glBindVertexArray(model->vaoID));
	ModelTexture* texture = texturedModel->GetTexture();
	m_Shader.LoadNumberOfRows(texture->GetNrOfRows());
	if (texture->IsTransparant())
	{
		MasterRenderer::DisableCulling();
	}
	m_Shader.LoadFakeLighting(texture->UsingFakeLighting());
	m_Shader.LoadShineVariables(texture->GetShineDamper(), texture->GetReflectivity());
	texture->Bind();
}

void EntityRenderer::UnbindTexturedModel()
{
	MasterRenderer::EnableCulling();
	GLCall(glBindVertexArray(0));
	
}

void EntityRenderer::PrepareInstance(Entity * entity)
{
	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity->GetTransform());
	m_Shader.LoadTransformationMatrix(transformationMatrix);
	m_Shader.LoadOffset(entity->GetTextureXOffset(), entity->GetTextureYOffset());
}

