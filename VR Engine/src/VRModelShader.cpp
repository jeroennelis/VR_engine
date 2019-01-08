#include "VRModelShader.h"



VRModelShader::VRModelShader(const std::string & path)
	:Shader(path)
{
}


VRModelShader::~VRModelShader()
{
}

void VRModelShader::LoadLocationMatrix(glm::mat4 & matrix)
{
	Shader::LoadUniformMatrix("matrix", matrix);
}
