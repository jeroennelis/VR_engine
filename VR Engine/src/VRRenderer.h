#pragma once
#include <openvr.h>

#include "VRModelShader.h"
#include "VRSettings.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VRModelShader.h"
#include "companionWindow.h"
#include "companionWindowShader.h"

class VRRenderer
{
public:
	VRRenderer(CompanionWindow * companionWindow);
	~VRRenderer();

	void renderVRModels(VRSettings &settings, vr::Hmd_Eye nEye);
	void renderCompanionWindow();

private:
	VRModelShader * m_VRModelShader;
	CompanionWindowShader * m_companionWindowShader;

	CompanionWindow *m_companionWindow;

};

