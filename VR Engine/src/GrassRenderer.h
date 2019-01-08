#pragma once
#include "GrassShader.h"
#include "Scene.h"

class GrassRenderer
{
private:
	GrassShader m_Shader;

public:
	GrassRenderer();
	~GrassRenderer();

	void LoadProjectionMatrix(glm::mat4& projectionMatrix);
	void Render(Scene* scene, const glm::mat4& viewProjectionMatrix);
};

