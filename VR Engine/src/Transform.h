#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include "Component.h"



class  Transform : public Component
{
public:
	Transform();
	~Transform();
	
	// Inherited via Component
	void Start() override;
	void Update() override;
	virtual void ShowInpectorInfo() override;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale = glm::vec3(1.0f,1.0f,1.0f);
};
