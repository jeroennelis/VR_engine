#pragma once
#include "Component.h"
#include "Transform.h"
#include "Terrain.h"

class Move :
	public Component
{
public:
	Move(Transform * transform, Terrain * terrain);
	~Move();

	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void ShowInpectorInfo() override;

private:
	const float RUN_SPEED = 12;
	const float SIDE_SPEED = 8;
	const float TURN_SPEED = 160;
	const float GRAVITY = -9.81f;
	const float JUMP_POWER = 18;

	const float TERRAIN_HEIGHT = 0;

	float m_CurrentSpeed = 0;
	float m_CurrentTurnSpeed = 0;
	float m_CurrentSideSpeed = 0;
	float m_CurrentUpwardsSpeed = 0;

	Transform * m_Transform;
	Terrain * m_Terrain;

	void CheckInputs();
	void CalulateNewTransform();

};

