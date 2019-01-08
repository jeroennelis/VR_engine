#pragma once
#include "GL.h"
#include "StaticShader.h"
#include "Scene.h"
#include "MeshRenderer.h"

class MasterRenderer;

class EntityRenderer
{
private:
	
	StaticShader m_Shader;

public:
	EntityRenderer();
	~EntityRenderer();

	void LoadProjectionMatrix(glm::mat4 & projectionMatrix);
	void Render(Scene * scene, const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane);

private:
	
	void PrepareTexturedModel(TexturedModel * texturedModel);
	void UnbindTexturedModel();
	void PrepareInstance(Entity * entity);
};

