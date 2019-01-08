#include "Quaternion.h"


Quaternion::Quaternion(float x, float y, float z, float w)
	:X(x), Y(y), Z(z), W(w)
{
}

Quaternion::~Quaternion()
{
}

void Quaternion::Normalize()
{
	float mag = (float)sqrt(W * W + X * X + Y * Y + Z * Z);
	W /= mag;
	X /= mag;
	Y /= mag;
	Z /= mag;
}

const glm::mat4 Quaternion::ToRotationMatrix() const 
{
	glm::mat4 matrix = glm::mat4();
	const float xy = X * Y;
	const float xz = X * Z;
	const float xw = X * W;
	const float yz = Y * Z;
	const float yw = Y * W;
	const float zw = Z * W;
	const float xSquared = X * X;
	const float ySquared = Y * Y;
	const float zSquared = Z * Z;

	matrix[0][0] = 1 - 2 * (ySquared + zSquared);
	matrix[0][1] = 2 * (xy - zw);
	matrix[0][2] = 2 * (xz + yw);
	matrix[0][3] = 0;
	matrix[1][0] = 2 * (xy + zw);
	matrix[1][1] = 1 - 2 * (xSquared + zSquared);
	matrix[1][2] = 2 * (yz - xw);
	matrix[1][3] = 0;
	matrix[2][0] = 2 * (xz - yw);
	matrix[2][1] = 2 * (yz + xw);
	matrix[2][2] = 1 - 2 * (xSquared + ySquared);
	matrix[2][3] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	return matrix;
}

Quaternion Quaternion::FromMatrix(glm::mat4 & matrix)
{
	float w, x, y, z;
	float diagonal = matrix[0][0] + matrix[1][1] + matrix[2][2];
	if (diagonal > 0) {
		float w4 = (float)(sqrt(diagonal + 1.0) * 2.0);
		w = w4 / 4.0;
		x = (matrix[1][2] - matrix[2][1]) / w4;
		y = (matrix[2][0] - matrix[0][2]) / w4;
		z = (matrix[0][1] - matrix[1][0]) / w4;
	}
	else if ((matrix[0][0] > matrix[1][1]) && (matrix[0][0] > matrix[2][2])) {
		float x4 = (float)(sqrt(1.0 + matrix[0][0] - matrix[1][1] - matrix[2][1]) * 2.0);
		w = (matrix[1][2] - matrix[2][1]) / x4;
		x = x4 / 4.0;
		y = (matrix[1][0] + matrix[0][1]) / x4;
		z = (matrix[2][0] + matrix[0][2]) / x4;
	}
	else if (matrix[1][1] > matrix[2][2]) {
		float y4 = (float)(sqrt(1.0 + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 2.0);
		w = (matrix[2][0] - matrix[0][2]) / y4;
		x = (matrix[1][0] + matrix[0][1]) / y4;
		y = y4 / 4.0;
		z = (matrix[2][1] + matrix[1][2]) / y4;
	}
	else {
		float z4 = (float)(sqrt(1.0 + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 2.0);
		w = (matrix[0][1] - matrix[1][0]) / z4;
		x = (matrix[2][0] + matrix[0][2]) / z4;
		y = (matrix[2][1] + matrix[1][2]) / z4;
		z = z4 / 4.0;
	}
	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::Interpolate(Quaternion a, Quaternion b, float blend)
{
	Quaternion result(0, 0, 0, 1);
	float dot = a.W * b.W + a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	float blendI = 1.0 - blend;
	if (dot < 0) {
		result.W = blendI * a.W + blend * -b.W;
		result.X = blendI * a.X + blend * -b.X;
		result.Y = blendI * a.Y + blend * -b.Y;
		result.Z = blendI * a.Z + blend * -b.Z;
	}
	else {
		result.W = blendI * a.W + blend * b.W;
		result.X = blendI * a.X + blend * b.X;
		result.Y = blendI * a.Y + blend * b.Y;
		result.Z = blendI * a.Z + blend * b.Z;
	}
	result.Normalize();
	return result;
}
