#include "VRSettings.h"

std::string TrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError = NULL);

VRSettings::VRSettings()
	:m_PoseClasses("")
{
}


VRSettings::~VRSettings()
{
	Shutdown();
}

bool VRSettings::Init()
{
	vr::EVRInitError eError = vr::VRInitError_None;
	m_IVRSystem = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		m_IVRSystem = NULL;
		char buf[1024];
		sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		std::cout << buf << std::endl;
		//TODO show message box
		Shutdown();
		return false;
	}

	m_RenderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
	if (!m_RenderModels)
	{
		m_IVRSystem = NULL;
		vr::VR_Shutdown();

		char buf[1024];
		sprintf_s(buf, sizeof(buf), "Unable to get render model interface: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		//TODO show message box
		Shutdown();
		return false;
	}

	SetupCams();
	SetupRenderModels();
	if (!initCompositor())
	{
		printf("%s - Failed to initialize VR Compositor!\n", __FUNCTION__);
		Shutdown();
		return false;
	}
	return true;
}

void VRSettings::SetupCams()
{
	m_ProjectionMatrixLeft = Maths::GetHMDMatrixProjectionEye(vr::Eye_Left, m_IVRSystem);
	m_ProjectionMatrixRight = Maths::GetHMDMatrixProjectionEye(vr::Eye_Right, m_IVRSystem);
	m_EyePosLeft = Maths::GetHMDMatrixPoseEye(vr::Eye_Left, m_IVRSystem);
	m_EyePosRight = Maths::GetHMDMatrixPoseEye(vr::Eye_Right, m_IVRSystem);
}

void VRSettings::SetupRenderModels()
{

	for (uint32_t unTrackedDevice = vr::k_unTrackedDeviceIndex_Hmd + 1; unTrackedDevice < vr::k_unMaxTrackedDeviceCount; unTrackedDevice++)
	{
		if (!m_IVRSystem->IsTrackedDeviceConnected(unTrackedDevice))
			continue;

		SetupRenderModelForTrackedDevice(unTrackedDevice);
	}
}

void VRSettings::SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackedDeviceIndex)
{
	if (unTrackedDeviceIndex >= vr::k_unMaxTrackedDeviceCount)
		return;

	// try to find a model we've already set up
	const std::string sRenderModelName = TrackedDeviceString(m_IVRSystem,
		unTrackedDeviceIndex, vr::Prop_RenderModelName_String);

	VRDevice * pRenderModel = FindOrLoadRenderModel(sRenderModelName.c_str());

	std::cout << "device: " << sRenderModelName << "\t index: " << unTrackedDeviceIndex << std::endl;

	if (!pRenderModel)
	{
		std::string sTrackingSystemName = TrackedDeviceString(m_IVRSystem,
			unTrackedDeviceIndex, vr::Prop_TrackingSystemName_String);

		printf("Unable to load render model for tracked device %d (%s.%s)",
			unTrackedDeviceIndex, sTrackingSystemName.c_str(), sRenderModelName.c_str());
	}
	else
	{
		m_VRdevices[unTrackedDeviceIndex] = pRenderModel;
		m_TrackedDeviceVisible[unTrackedDeviceIndex] = true;
	}
}

VRDevice * VRSettings::FindOrLoadRenderModel(const char * pchRenderModelName)
{
	VRDevice *pRenderModel = NULL;
	for (std::vector< VRDevice * >::iterator i = m_vecRenderModels.begin(); i != m_vecRenderModels.end(); i++)
	{
		if (!_stricmp((*i)->GetName().c_str(), pchRenderModelName))
		{
			pRenderModel = *i;
			break;
		}
	}

	// load the model if we didn't find one
	if (!pRenderModel)
	{
		vr::RenderModel_t *pModel;
		vr::EVRRenderModelError error;
		while (1)
		{
			error = vr::VRRenderModels()->LoadRenderModel_Async(pchRenderModelName, &pModel);
			if (error != vr::VRRenderModelError_Loading)
				break;

			//Sleep(1);
		}

		if (error != vr::VRRenderModelError_None)
		{
			printf("Unable to load render model %s - %s\n", pchRenderModelName,
				vr::VRRenderModels()->GetRenderModelErrorNameFromEnum(error));

			return NULL; // move on to the next tracked device
		}

		vr::RenderModel_TextureMap_t *pTexture;
		while (1)
		{
			error = vr::VRRenderModels()->LoadTexture_Async(pModel->diffuseTextureId, &pTexture);
			if (error != vr::VRRenderModelError_Loading)
				break;

			//Sleep(1);
		}

		if (error != vr::VRRenderModelError_None)
		{
			printf("Unable to load render texture id:%d for render model %s\n",
				pModel->diffuseTextureId, pchRenderModelName);

			vr::VRRenderModels()->FreeRenderModel(pModel);
			return NULL; // move on to the next tracked device
		}

		pRenderModel = new VRDevice(pchRenderModelName);
		if (!pRenderModel->Init(*pModel, *pTexture))
		{
			printf("Unable to create GL model from render model %s\n", pchRenderModelName);
			delete pRenderModel;
			pRenderModel = NULL;
		}
		else
		{

			m_vecRenderModels.push_back(pRenderModel);
		}
		vr::VRRenderModels()->FreeRenderModel(pModel);
		vr::VRRenderModels()->FreeTexture(pTexture);
	}
	return pRenderModel;
}

std::string TrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError)
{
	uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, peError);
	if (unRequiredBufferLen == 0)
		return "";

	char *pchBuffer = new char[unRequiredBufferLen];
	unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
	std::string sResult = pchBuffer;
	delete[] pchBuffer;
	return sResult;
}

bool VRSettings::initCompositor()
{
	vr::EVRInitError peError = vr::VRInitError_None;

	if (!vr::VRCompositor())
	{
		printf("Compositor initialization failed. See log file for details\n");
		return false;
	}
	return true;
}



void VRSettings::Shutdown()
{
	if (m_IVRSystem)
	{
		vr::VR_Shutdown();
		m_IVRSystem = NULL;

		for (std::vector< VRDevice * >::iterator i = m_vecRenderModels.begin(); i != m_vecRenderModels.end(); i++)
		{
			delete (*i);
		}
	}
}

void VRSettings::UpdateHMDMatrixPose()
{
	if (!m_IVRSystem)
		return;

	vr::VRCompositor()->WaitGetPoses(m_TrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	m_ValidPoseCount = 0;
	m_PoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_TrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_ValidPoseCount++;
			m_DevicePoses[nDevice] = ConvertSteamVRMatrixToMatrix4(m_TrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);

			if (m_IVRSystem->GetTrackedDeviceClass(nDevice) == vr::TrackedDeviceClass_GenericTracker)
			{
				m_VRdevices[nDevice]->setHmdMatrix(m_DevicePoses[nDevice]);

			}

			if (m_DevClassChar[nDevice] == 0)
			{
				switch (m_IVRSystem->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:			m_DevClassChar[nDevice] = 'C'; break;		//controller
				case vr::TrackedDeviceClass_HMD:				m_DevClassChar[nDevice] = 'H'; break;		//Head Mounted Device
				case vr::TrackedDeviceClass_Invalid:			m_DevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_GenericTracker:		m_DevClassChar[nDevice] = 'G';	break;		//tracker
				case vr::TrackedDeviceClass_TrackingReference:	m_DevClassChar[nDevice] = 'T'; break;		//lighthouse
				default:										m_DevClassChar[nDevice] = '?'; break;
				}
			}
			m_PoseClasses += m_DevClassChar[nDevice];
		}
	}
	if (m_TrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_HMDPose = m_DevicePoses[vr::k_unTrackedDeviceIndex_Hmd];
		m_HMDPose = glm::inverse(m_HMDPose);
	}

	//TODO controller count
}

glm::mat4 VRSettings::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	glm::mat4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

glm::mat4 VRSettings::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	glm::mat4 matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = m_ProjectionMatrixLeft * m_EyePosLeft * m_HMDPose;
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = m_ProjectionMatrixRight * m_EyePosRight *  m_HMDPose;
	}

	return matMVP;
}
