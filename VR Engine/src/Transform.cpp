#include "Transform.h"
#include <imgui.h>


Transform::Transform()
{
	name = "Transform";
}

Transform::~Transform()
{
}

void Transform::Start()
{
}

void Transform::Update()
{
	/*std::cout << "Position: " << Position.x << ", "<<Position.y << ", " << Position.z << std::endl;
	std::cout << "Rotation: " << Rotation.x << ", " << Rotation.y << ", " << Rotation.z << std::endl;
	std::cout << "Scale: " << Scale.x << ", " << Scale.y << ", " << Scale.z << std::endl;*/
}

void Transform::ShowInpectorInfo()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::InputFloat3("Translate", &Position[0], 3);
		ImGui::InputFloat3("Rotate", &Rotation[0], 3);
		ImGui::InputFloat3("Scale", &Scale[0], 3);
		ImGui::TreePop();
	}	
}


