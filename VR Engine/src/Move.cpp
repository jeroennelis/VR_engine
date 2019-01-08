#include "Move.h"



Move::Move(Transform * transform, Terrain * terrain)
	:m_Transform(transform), m_Terrain(terrain)
{
	name = "Move";
}


Move::~Move()
{
}

void Move::Start()
{
}

void Move::Update()
{
	CheckInputs();
	CalulateNewTransform();
}

void Move::ShowInpectorInfo()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::TreePop();
	}
}

void Move::CheckInputs()
{
	if (ImGui::GetIO().KeysDown[GLFW_KEY_W])
	{
		m_CurrentSpeed = RUN_SPEED;
	}
	else if (ImGui::GetIO().KeysDown[GLFW_KEY_S])
	{
		m_CurrentSpeed = -RUN_SPEED;
	}
	else
	{
		m_CurrentSpeed = 0;
	}


	if (ImGui::GetIO().KeysDown[GLFW_KEY_Q])
	{
		m_CurrentTurnSpeed = TURN_SPEED;
	}
	else if (ImGui::GetIO().KeysDown[GLFW_KEY_E])
	{
		m_CurrentTurnSpeed = -TURN_SPEED;
	}
	else
	{
		m_CurrentTurnSpeed = 0;
	}

	if (ImGui::GetIO().KeysDown[GLFW_KEY_A])
	{
		m_CurrentSideSpeed = SIDE_SPEED;
	}
	else if (ImGui::GetIO().KeysDown[GLFW_KEY_D])
	{
		m_CurrentSideSpeed = -SIDE_SPEED;
	}
	else
	{
		m_CurrentSideSpeed = 0;
	}

	if (ImGui::GetIO().KeysDown[GLFW_KEY_SPACE])
	{
		/*Jump();*/
	}
}

void Move::CalulateNewTransform()
{
	float delta = ImGui::GetIO().DeltaTime;
	m_Transform->Rotation.y += m_CurrentTurnSpeed * delta;
	float distance = m_CurrentSpeed * delta;
	float sideDistance = m_CurrentSideSpeed * delta;
	m_Transform->Position.x += distance * sin(glm::radians(m_Transform->Rotation.y)) + sideDistance * cos(glm::radians(m_Transform->Rotation.y));
	m_Transform->Position.z += distance * cos(glm::radians(m_Transform->Rotation.y)) - sideDistance * sin(glm::radians(m_Transform->Rotation.y));
	float terrainHeight = m_Terrain->GetHeightOfTerrain(m_Transform->Position.x, m_Transform->Position.z);

	m_CurrentUpwardsSpeed += GRAVITY * delta;
	m_Transform->Position.y += m_CurrentUpwardsSpeed * delta;

	if (m_Transform->Position.y < terrainHeight)
	{
		m_CurrentUpwardsSpeed = 0;
		m_Transform->Position.y = terrainHeight;
		//m_InAir = false;
	}
}
