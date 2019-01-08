#pragma once
#include "Shader.h"
#include "Maths.h"
#include "Camera.h"

class PointCloudShader :
	public Shader
{
public:
	PointCloudShader(const std::string& filepath);
	~PointCloudShader();

	void LoadTransformationMatrix(glm::mat4 & matrix);
	void LoadProjectionMatrix(glm::mat4 & matrix);
	void LoadViewMatrix(GameObject * cameraObject);
	void LoadUsingVR(bool value);
	void LoadVRMatrix(glm::mat4 & matrix);
};

