#pragma once
#include "Shader.h"
class GuiShader :
	public Shader
{
public:
	GuiShader(const std::string& filepath);
	~GuiShader();

	void LoadTransformationMatrix(glm::mat4 & matrix);

};

