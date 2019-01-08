#pragma once
#include "Shader.h"
#include "GameObject.h"
#include "Maths.h"

class GrassShader :
	public Shader
{
public:
	GrassShader(const std::string& filepath);
	~GrassShader();

	void LoadTransformationMatrix(glm::mat4 & matrix);
	void LoadProjectionMatrix(glm::mat4 & matrix);
	void LoadViewMatrix(GameObject * cameraObject);
};

