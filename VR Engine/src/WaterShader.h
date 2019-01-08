#pragma once
#include "Shader.h"
#include "GameObject.h"
#include "Maths.h"
#include "Light.h"

class WaterShader :
	public Shader
{
public:
	WaterShader(const std::string& filepath);
	~WaterShader();

	void LoadTransformationMatrix(glm::mat4 & matrix);
	void LoadViewMatrix(GameObject * cameraObject);
	void LoadProjectionMatrix(glm::mat4 & matrix);
	void LoadVRMatrix(glm::mat4 & matrix);
	void ConnectTextureUnits();
	void LoadMoveFactor(float factor);
	void LoadLight(GameObject * light);
};

