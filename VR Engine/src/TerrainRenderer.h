#pragma once
#include "TerrainShader.h"
#include "Terrain.h"
#include "TerrainTexturePack.h"
#include "Scene.h"

class MasterRenderer;

class TerrainRenderer
{
private:
	TerrainShader m_Shader;

public:
	TerrainRenderer();
	~TerrainRenderer();

	void Render(Scene * scene, const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane);
	
	void LoadProjectionMatrix(glm::mat4 & projectionMatrix);
private:
	void PrepareTerrain(Terrain * terrain);
	void UnbindTexturedModel();
	void LoadModelMatrix(Terrain * terrain);
	void BindTextures(Terrain * terrain);
};

