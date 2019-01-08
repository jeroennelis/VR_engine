#pragma once
#include <GLM\glm.hpp>
#include "Shader.h"
#include "Light.h"
#include "Maths.h"

class TerrainShader : public Shader
{
public:
	TerrainShader(const std::string& filepath);
	~TerrainShader();

	void LoadTransformationMatrix(glm::mat4 & matrix);
	void LoadProjectionMatrix(glm::mat4 & matrix);
	void LoadViewMatrix(GameObject * cameraObject);
	void loadLight(GameObject * light);
	void LoadShineVariables(float shineDamper, float reflectivity);
	void LoadSkyColour(float r, float g, float b);
	void ConnectTextureUnits();
	void LoadUsingVR(bool value);
	void LoadVRMatrix(const glm::mat4 & matrix);
	void LoadClipPlane(const glm::vec4 & plane);

private:
	
};

