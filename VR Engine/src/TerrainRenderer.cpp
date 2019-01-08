#include "TerrainRenderer.h"
#include "MasterRenderer.h"


TerrainRenderer::TerrainRenderer()
	:m_Shader("res/shaders/Terrain.shader")
{
	m_Shader.Bind();
	m_Shader.ConnectTextureUnits();
	m_Shader.Unbind();
}


TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::LoadProjectionMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}

void TerrainRenderer::Render(Scene * scene, const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane)
{
	{
		m_Shader.Bind();
		m_Shader.LoadClipPlane(clipPlane);
		m_Shader.LoadUsingVR(scene->IsUsingVR());
		m_Shader.loadLight(scene->GetLight());
		m_Shader.LoadViewMatrix(scene->GetCurrentCamera());
		m_Shader.LoadSkyColour(MasterRenderer::RED, MasterRenderer::GREEN, MasterRenderer::BLUE);
	
		std::vector<GameObject*> * terrains = scene->GetTerrains();

		for (GameObject * terrain : *terrains)
		{
			Terrain * terrainComponent = terrain->GetComponent<Terrain>();
			PrepareTerrain(terrainComponent);
			LoadModelMatrix(terrainComponent);
			m_Shader.LoadVRMatrix(viewProjectionMatrix);
			glDrawElements(GL_TRIANGLES, terrainComponent->GetRawModel()->vertexCount, GL_UNSIGNED_INT, 0);
			UnbindTexturedModel();
		}
		m_Shader.Unbind();
	}
}


void TerrainRenderer::PrepareTerrain(Terrain * terrain)
{

	RawModel* model = terrain->GetRawModel();
	GLCall(glBindVertexArray(model->vaoID));
	BindTextures(terrain);
	m_Shader.LoadShineVariables(1, 0);
	
}

void TerrainRenderer::UnbindTexturedModel()
{
	GLCall(glBindVertexArray(0));
}

void TerrainRenderer::LoadModelMatrix(Terrain * terrain)
{
	glm::vec3 position(terrain->GetX(), 0.0f, terrain->GetZ());
	Trans transform(position, 0.0f, 0.0f, 0.0f, 1);
	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(transform);
	m_Shader.LoadTransformationMatrix(transformationMatrix);
}

void TerrainRenderer::BindTextures(Terrain * terrain)
{
	TerrainTexturePack * texturePack = terrain->GetTexturePack();
	texturePack->GetBackgroundTexture()->Bind(0);
	texturePack->GetRTexture()->Bind(1);
	texturePack->GetGTexture()->Bind(2);
	texturePack->GetBTexture()->Bind(3);
	terrain->GetBlendMap()->Bind(4);

}
