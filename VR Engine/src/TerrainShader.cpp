#include "TerrainShader.h"



TerrainShader::TerrainShader(const std::string& filepath)
	:Shader(filepath)
{
}


TerrainShader::~TerrainShader()
{
}

void TerrainShader::LoadTransformationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}

void TerrainShader::LoadProjectionMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void TerrainShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
}

void TerrainShader::loadLight(GameObject * light)
{
	glm::vec3 position = light->GetComponent<Transform>()->Position;
	Shader::LoadUniform3f("u_lightPosition", position.x, position.y, position.z);
	glm::vec3 colour = light->GetComponent<Light>()->Color;
	Shader::LoadUniform3f("u_lightColour", colour.x, colour.y, colour.z);
}

void TerrainShader::LoadShineVariables(float shineDamper, float reflectivity)
{
	Shader::LoadUniform1f("u_shineDamper", shineDamper);
	Shader::LoadUniform1f("u_reflectivity", reflectivity);
}

void TerrainShader::LoadSkyColour(float r, float g, float b)
{
	Shader::LoadUniform3f("u_skyColour", r, g, b);
}

void TerrainShader::ConnectTextureUnits()
{
	Shader::LoadUniform1i("backgroundTexture", 0);
	Shader::LoadUniform1i("rTexture", 1);
	Shader::LoadUniform1i("gTexture", 2);
	Shader::LoadUniform1i("bTexture", 3);
	Shader::LoadUniform1i("blendMap", 4);
}

void TerrainShader::LoadUsingVR(bool value)
{
	Shader::LoadBool("u_usingVR", value);
}

void TerrainShader::LoadVRMatrix(const glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_VRMatrix", matrix);
}

void TerrainShader::LoadClipPlane(const glm::vec4 & plane)
{
	Shader::LoadUniform4f("u_clipPlane", plane.x, plane.y, plane.z, plane.w);
}
