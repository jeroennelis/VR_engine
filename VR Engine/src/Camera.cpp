#include "Camera.h"



Camera::Camera(Transform * transform)
	:m_Transform(transform)
{
	name = "Camera";
	Yaw = 0;
	Pitch = 20;
}


Camera::~Camera()
{
}

void Camera::Start()
{
}

void Camera::Update()
{
	if (focussedAroundPlayer)
	{
		CalculateZoom();
		CalculatePitch();
		CalculateAngleAroundPlayer();
		float horizontalDistance = CalculateHorizontalDistance();
		float verticalDistance = CalculateVerticalDistance() + 0;
		CalculateCamPosition(horizontalDistance, verticalDistance);
		Yaw = 180 - (m_PlayerTransform->Rotation.y + m_AngleAroundPlayer);
	}
}

void Camera::ShowInpectorInfo()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::InputFloat("Pitch", &Pitch, 1);
		ImGui::InputFloat("Yaw", &Yaw, 1);
		ImGui::InputFloat("Roll", &Roll, 1);
		ImGui::InputFloat("FOV", &FOV, 1); 
		ImGui::InputFloat("NEAR", &NEAR, 1);
		ImGui::InputFloat("FAR", &FAR, 1);
		ImGui::Checkbox("player", &focussedAroundPlayer);
		
		ImGui::TreePop();
	}
}

void Camera::CalculateZoom()
{
	float zoomLevel = ImGui::GetIO().MouseWheel;
	if (zoomLevel > 0)
		std::cout << zoomLevel << std::endl;
	m_DistanceFromPlayer -= zoomLevel * 0.1f;
}

void Camera::CalculatePitch()
{
	/*if (ImGui::IsMouseDown(1))
	{
		Pitch -= ImGui::GetMousePos().y * 0.1f;
	}*/
}

void Camera::CalculateAngleAroundPlayer()
{
	/*if (Window::IsMouseButtonPressed(0))
	{
		m_AngleAroundPlayer -= Window::GetDX() * 0.3f;
	}*/
}

float Camera::CalculateHorizontalDistance()
{
	return (float)m_DistanceFromPlayer * cos(glm::radians(Pitch));
}

float Camera::CalculateVerticalDistance()
{
	return (float)m_DistanceFromPlayer * sin(glm::radians(Pitch));
}

void Camera::CalculateCamPosition(float horizontalDistance, float verticalDistance)
{
	
	float angle = m_PlayerTransform->Rotation.y + m_AngleAroundPlayer;
	float offsetX = (float)(horizontalDistance * sin(glm::radians(angle)));
	float offsetZ = (float)(horizontalDistance * cos(glm::radians(angle)));
	m_Transform->Position.x = m_PlayerTransform->Position.x - offsetX;
	m_Transform->Position.y = m_PlayerTransform->Position.y + verticalDistance;
	m_Transform->Position.z = m_PlayerTransform->Position.z - offsetZ;
}
