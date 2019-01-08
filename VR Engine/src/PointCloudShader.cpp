#include "PointCloudShader.h"



PointCloudShader::PointCloudShader(const std::string& filepath)
	:Shader(filepath)
{
}


PointCloudShader::~PointCloudShader()
{
}

void PointCloudShader::LoadTransformationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}

void PointCloudShader::LoadProjectionMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_projectionMatrix", matrix);
}

void PointCloudShader::LoadViewMatrix(GameObject * cameraObject)
{
	glm::mat4 matrix = Maths::CreateViewMatrix(cameraObject);
	Shader::LoadUniformMatrix("u_viewMatrix", matrix);
}

void PointCloudShader::LoadUsingVR(bool value)
{
	Shader::LoadBool("u_usingVR", value);
}

void PointCloudShader::LoadVRMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_VRMatrix", matrix);
}
