#include "Maths.h"


Maths::Maths()
{
}


Maths::~Maths()
{
}

glm::mat4 Maths::CreateTransformationMatrix(Trans & transform)
{
	glm::mat4 posMatrix = glm::translate(transform.m_Position);

	glm::mat4 rotXMatrix = glm::rotate(glm::radians(transform.m_RotX), glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(glm::radians(transform.m_RotY), glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(glm::radians(transform.m_RotZ), glm::vec3(0, 0, 1));
	glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

	glm::mat4 scaleMatrix = glm::scale(glm::vec3(transform.m_Scale, transform.m_Scale, transform.m_Scale));
	glm::mat4 test = posMatrix * rotMatrix * scaleMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

glm::mat4 Maths::CreateTransformationMatrix(Transform * transform)
{
	glm::mat4 posMatrix = glm::translate(transform->Position);

	glm::mat4 rotXMatrix = glm::rotate(glm::radians(transform->Rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(glm::radians(transform->Rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(glm::radians(transform->Rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

	glm::mat4 scaleMatrix = glm::scale(glm::vec3(transform->Scale.x, transform->Scale.y, transform->Scale.z));
	glm::mat4 test = posMatrix * rotMatrix * scaleMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

glm::mat4 Maths::CreateViewMatrix(GameObject * cameraObject)
{
	glm::mat4 viewMatrix;

	Camera * camera = cameraObject->GetComponent<Camera>();
	Transform * transform = cameraObject->GetComponent<Transform>();

	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->Pitch), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->Yaw), glm::vec3(0, 1, 0));

	glm::vec3 negativeCamPos(-transform->Position.x, -transform->Position.y, -transform->Position.z);
	viewMatrix = glm::translate(viewMatrix, negativeCamPos);

	return viewMatrix;
}

float Maths::BarryCentric(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3, const glm::vec2 & pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

glm::mat4 Maths::CreateTransformationMatrix(const glm::vec2 & translation, const glm::vec2 & scale)
{
	glm::mat4 posMatrix = glm::translate(glm::vec3(translation.x, translation.y, 0));
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale.x, scale.y, 1));

	return posMatrix * scaleMatrix;
}


//VR Maths

glm::mat4 Maths::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye, vr::IVRSystem * ivrSystem)
{
	if (!ivrSystem)
		return glm::mat4();

	vr::HmdMatrix44_t mat = ivrSystem->GetProjectionMatrix(nEye, Window::NEAR_PLANE, Window::FAR_PLANE);

	return glm::mat4(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);
}

glm::mat4 Maths::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye, vr::IVRSystem * ivrSystem)
{
	if (!ivrSystem)
		return glm::mat4();

	vr::HmdMatrix34_t matEyeRight = ivrSystem->GetEyeToHeadTransform(nEye);
	glm::mat4 matrixObj(
		matEyeRight.m[0][0], matEyeRight.m[1][0], matEyeRight.m[2][0], 0.0,
		matEyeRight.m[0][1], matEyeRight.m[1][1], matEyeRight.m[2][1], 0.0,
		matEyeRight.m[0][2], matEyeRight.m[1][2], matEyeRight.m[2][2], 0.0,
		matEyeRight.m[0][3], matEyeRight.m[1][3], matEyeRight.m[2][3], 1.0f
	);

	return glm::inverse(matrixObj);
}
