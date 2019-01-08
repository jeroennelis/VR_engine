#pragma once
#include "Component.h"
#include "Transform.h"
class Camera :
	public Component
{
public:
	Camera(Transform * transform);
	~Camera();

	inline void SetPlayerTransform(Transform * transform) { m_PlayerTransform = transform; }

public:
	float Pitch = 0;
	float Yaw = 0;
	float Roll = 0;
	
	float FOV = 70;
	float NEAR = 0.1f;
	float FAR = 1000.0;
	bool focussedAroundPlayer = true;

private:
	Transform * m_Transform;
	Transform * m_PlayerTransform;
	float m_DistanceFromPlayer = 10;
	float m_AngleAroundPlayer = 0;
	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void ShowInpectorInfo() override;

	void CalculateZoom();
	void CalculatePitch();
	void CalculateAngleAroundPlayer();
	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();
	void CalculateCamPosition(float horizontalDistance, float verticalDistance);	
};

