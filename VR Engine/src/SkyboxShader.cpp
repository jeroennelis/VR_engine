#include "SkyboxShader.h"



SkyboxShader::SkyboxShader(const std::string& filepath)
	:Shader(filepath)
{
	Bind();

	ConnectTextureUnits();

	Unbind();
}


SkyboxShader::~SkyboxShader()
{
}

void SkyboxShader::LoadProjectionMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void SkyboxShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
}

void SkyboxShader::ConnectTextureUnits()
{
	Shader::LoadUniform1i("cubeMap", 0);
}
