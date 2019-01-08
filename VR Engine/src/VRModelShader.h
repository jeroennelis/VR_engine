#pragma once
#include <iostream>
#include "Shader.h"

class VRModelShader :
	public Shader
{
public:
	VRModelShader(const std::string & path);
	~VRModelShader();

	void LoadLocationMatrix(glm::mat4 & matrix);
};

