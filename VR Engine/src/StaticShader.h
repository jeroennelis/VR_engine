#pragma once
#include "Shader.h"
#include "Maths.h"
#include "Light.h"

class StaticShader :
	public Shader
{
public:
	StaticShader(const std::string& filepath);
	~StaticShader();

	void LoadTransformationMatrix(glm::mat4 & matrix) ;
	void LoadProjectionMatrix(glm::mat4 & matrix) ;
	void LoadViewMatrix(GameObject * cameraObject);
	void loadLight(GameObject * light) ;
	void LoadShineVariables(float shineDamper, float reflectivity) ;
	void LoadFakeLighting(bool useFake);
	void LoadSkyColour(float r, float g, float b);
	void LoadNumberOfRows(int nrOfRows);
	void LoadOffset(float x, float y);
	void LoadUsingVR(bool value);
	void LoadVRMatrix(const glm::mat4 & matrix);
	void LoadClipPlane(const glm::vec4 & plane);
};

