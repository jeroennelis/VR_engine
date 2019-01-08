#include "StaticShader.h"



StaticShader::StaticShader(const std::string& filepath)
	:Shader(filepath)
{
}


StaticShader::~StaticShader()
{
}

void StaticShader::LoadTransformationMatrix(glm::mat4 & matrix) 
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}


void StaticShader::LoadProjectionMatrix(glm::mat4 & matrix) 
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void StaticShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
}

void StaticShader::loadLight(GameObject * light)
{
	glm::vec3 position = light->GetComponent<Transform>()->Position;
	Shader::LoadUniform3f("u_lightPosition", position.x, position.y, position.z);
	glm::vec3 colour = light->GetComponent<Light>()->Color;
	Shader::LoadUniform3f("u_lightColour", colour.x, colour.y, colour.z);
}

void StaticShader::LoadShineVariables(float shineDamper, float reflectivity) 
{
	Shader::LoadUniform1f("u_shineDamper", shineDamper);
	Shader::LoadUniform1f("u_reflectivity",reflectivity);
}

void StaticShader::LoadFakeLighting(bool useFake)
{
	Shader::LoadBool("u_useFakeLighting", useFake);
}

void StaticShader::LoadSkyColour(float r, float g, float b)
{
	Shader::LoadUniform3f("u_skyColour", r, g, b);
}

void StaticShader::LoadNumberOfRows(int nrOfRows)
{
	Shader::LoadUniform1f("u_numberOfRows", (float)nrOfRows);
}

void StaticShader::LoadOffset(float x, float y)
{
	Shader::LoadUniform2f("u_offset", x, y);
}

void StaticShader::LoadUsingVR(bool value)
{
	Shader::LoadBool("u_usingVR", value);
}

void StaticShader::LoadVRMatrix(const glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_VRMatrix", matrix);
}

void StaticShader::LoadClipPlane(const glm::vec4 & plane)
{
	Shader::LoadUniform4f("u_clipPlane", plane.x, plane.y, plane.z, plane.w);
}
