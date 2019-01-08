#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <openvr.h>
#include <GLM\glm.hpp>

#include "Window.h"
#include "Maths.h"
#include "VRDevice.h"


class VRSettings
{
public:
	VRSettings();
	~VRSettings();

	bool Init();
	void Shutdown();
	
	void UpdateHMDMatrixPose();

	inline vr::IVRSystem * GetIVRSystem() { return m_IVRSystem; }

	glm::mat4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);

	inline VRDevice **GetTrackedDeviceToRenderModel() { return m_VRdevices; }

	inline bool * IsShowTrackedDevice() { return m_TrackedDeviceVisible; }

	inline vr::TrackedDevicePose_t * GetTrackedDevicePose() { return m_TrackedDevicePose; }

	glm::mat4 *GetDevicePose() { return m_DevicePoses; }

private:
	vr::IVRSystem *m_IVRSystem;
	vr::IVRRenderModels *m_RenderModels;

	glm::mat4 m_HMDPose;
	glm::mat4 m_ProjectionMatrixLeft;
	glm::mat4 m_ProjectionMatrixRight;
	glm::mat4 m_EyePosLeft;
	glm::mat4 m_EyePosRight;

	VRDevice * m_VRdevices[vr::k_unMaxTrackedDeviceCount];
	std::vector<VRDevice *> m_vecRenderModels;
	bool m_TrackedDeviceVisible[vr::k_unMaxTrackedDeviceCount];

	vr::TrackedDevicePose_t m_TrackedDevicePose[vr::k_unMaxTrackedDeviceCount];

	int m_ValidPoseCount;
	int m_ValidPoseCount_Last;

	std::string m_PoseClasses;

	glm::mat4 m_DevicePoses[vr::k_unMaxTrackedDeviceCount];

	char m_DevClassChar[vr::k_unMaxTrackedDeviceCount];


private:
	void SetupCams();
	void SetupRenderModels();
	bool initCompositor();

	void SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackedDeviceIndex);
	VRDevice * FindOrLoadRenderModel(const char * pchRenderModelName);
	glm::mat4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
};

