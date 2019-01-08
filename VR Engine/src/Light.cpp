#include "Light.h"



Light::Light()
{
	name = "light";
	Color = glm::vec3(1, 1, 1);
}


Light::~Light()
{
}

void Light::Start()
{
}

void Light::Update()
{
}

void Light::ShowInpectorInfo()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::InputFloat("RED", &Color[0], 0.1);
		ImGui::InputFloat("GREEN", &Color[1], 0.1);
		ImGui::InputFloat("BLUE", &Color[2], 0.1);
		ImGui::TreePop();
	}
}
