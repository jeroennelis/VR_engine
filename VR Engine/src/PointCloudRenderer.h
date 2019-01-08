#pragma once
#include "PointCloudShader.h"
#include "Scene.h"

class PointCloudRenderer
{
private:
	PointCloudShader m_Shader;

public:
	PointCloudRenderer();
	~PointCloudRenderer();

	void LoadProjectionMatrix(glm::mat4 & projectionMatrix);
	void Render(Scene * scene, glm::mat4 & viewProjectionMatrix);
};

