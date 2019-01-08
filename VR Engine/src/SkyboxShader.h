#pragma once
#include "Shader.h"
#include "GameObject.h"
#include "Maths.h"

class SkyboxShader :
	public Shader
{
public:
	SkyboxShader(const std::string& filepath);
	~SkyboxShader();
	
	void LoadProjectionMatrix(glm::mat4 & matrix);
	void LoadViewMatrix(GameObject * cameraObject);
	void ConnectTextureUnits();
};

