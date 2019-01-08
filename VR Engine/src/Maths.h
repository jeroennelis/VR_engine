#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <openvr.h>
#include "Entity.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Window.h"


class Maths
{
public:
	Maths();
	~Maths();

	static glm::mat4 CreateTransformationMatrix(Trans & transform);
	static glm::mat4 CreateTransformationMatrix(Transform * transform);
	static glm::mat4 CreateViewMatrix(GameObject * cameraObject);
	static float BarryCentric(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3, const glm::vec2 & pos);
	static glm::mat4 CreateTransformationMatrix(const glm::vec2 & translation, const glm::vec2 & scale);
	static glm::mat4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye, vr::IVRSystem * ivrSystem);
	static glm::mat4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye, vr::IVRSystem * ivrSystem);
};

