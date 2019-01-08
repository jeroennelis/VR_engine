#include "WaterShader.h"



WaterShader::WaterShader(const std::string& filepath)
	:Shader(filepath)
{
}

WaterShader::~WaterShader()
{
}

void WaterShader::LoadTransformationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}

void WaterShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
	glm::vec3 pos = cameraObject->GetComponent<Transform>()->Position;
	Shader::LoadUniform3f("u_cameraPosition", pos.x, pos.y, pos.z );
}

void WaterShader::LoadProjectionMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void WaterShader::LoadVRMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_VRMatrix", matrix);
}

void WaterShader::ConnectTextureUnits()
{
	Shader::LoadUniform1i("reflectionTexture", 0);
	Shader::LoadUniform1i("refractionTexture", 1);
	Shader::LoadUniform1i("dudvMap", 2);
	Shader::LoadUniform1i("normalMap", 3);
	Shader::LoadUniform1i("depthMap", 4);
}

void WaterShader::LoadMoveFactor(float factor)
{
	Shader::LoadUniform1f("u_moveFactor", factor);
}

void WaterShader::LoadLight(GameObject * light)
{
	glm::vec3 position = light->GetComponent<Transform>()->Position;
	Shader::LoadUniform3f("u_lightPosition", position.x, position.y, position.z);
	glm::vec3 colour = light->GetComponent<Light>()->Color;
	Shader::LoadUniform3f("u_lightColour", colour.x, colour.y, colour.z);
}




