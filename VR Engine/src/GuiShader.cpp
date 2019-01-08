#include "GuiShader.h"



GuiShader::GuiShader(const std::string& filepath)
	:Shader(filepath)
{
}


GuiShader::~GuiShader()
{
}

void GuiShader::LoadTransformationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("u_transformationMatrix", matrix);
}
