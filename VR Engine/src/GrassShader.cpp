#include "GrassShader.h"



GrassShader::GrassShader(const std::string& filepath)
	:Shader(filepath)
{
}


GrassShader::~GrassShader()
{
}

void GrassShader::LoadTransformationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}

void GrassShader::LoadProjectionMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void GrassShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
}
