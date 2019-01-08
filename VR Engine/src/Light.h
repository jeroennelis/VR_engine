#pragma once
#include "Component.h"
#include "GLM/glm.hpp"

class Light :
	public Component
{
public:
	Light();
	~Light();

	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void ShowInpectorInfo() override;

	glm::vec3 Color;
};

