#pragma once
#include <iostream>
#include <imgui.h>

class Component
{
public:
	
	virtual void Start() = 0;
	virtual void Update() = 0;

	virtual void ShowInpectorInfo() = 0;
	std::string name;

};

