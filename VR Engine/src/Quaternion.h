#pragma once

#include <GLM/glm.hpp>
#include <math.h> 

class Quaternion
{

public:
	float X;
	float Y;
	float Z;
	float W;

public:
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	void Normalize();
	const glm::mat4  ToRotationMatrix()const;
	static Quaternion FromMatrix(glm::mat4 & matrix);
	static Quaternion Interpolate(Quaternion a, Quaternion b, float blend);
};

