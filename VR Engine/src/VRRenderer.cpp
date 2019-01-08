#include "VRRenderer.h"



VRRenderer::VRRenderer(CompanionWindow * companionWindow)
	:m_companionWindow(companionWindow)
{
	m_VRModelShader = new VRModelShader("res/shaders/VRModel.shader");
	m_companionWindowShader = new CompanionWindowShader("res/shaders/CompanionWindow.shader");
}


VRRenderer::~VRRenderer()
{
	delete m_VRModelShader;
	delete m_companionWindowShader;
}

void VRRenderer::renderVRModels(VRSettings & settings, vr::Hmd_Eye nEye)
{
	m_VRModelShader->Bind();

	for (uint32_t unTrackedDevice = 0; unTrackedDevice < vr::k_unMaxTrackedDeviceCount; unTrackedDevice++)
	{
		if (!settings.GetTrackedDeviceToRenderModel()[unTrackedDevice] || !settings.IsShowTrackedDevice()[unTrackedDevice])
			continue;

		const vr::TrackedDevicePose_t & pose = settings.GetTrackedDevicePose()[unTrackedDevice];
		if (!pose.bPoseIsValid)
			continue;

		/*if (settings.GetIVRSystem()->IsInputFocusCapturedByAnotherProcess() && settings.GetIVRSystem()->GetTrackedDeviceClass(unTrackedDevice) == vr::TrackedDeviceClass_Controller)
			continue;*/

		const glm::mat4 & matDeviceToTracking = settings.GetDevicePose()[unTrackedDevice];
		glm::mat4 matMVP = settings.GetCurrentViewProjectionMatrix(nEye) * matDeviceToTracking;
		m_VRModelShader->LoadLocationMatrix(matMVP);

		settings.GetTrackedDeviceToRenderModel()[unTrackedDevice]->Draw();
	}

	m_VRModelShader->Unbind();
}

void VRRenderer::renderCompanionWindow()
{
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Window::Width, Window::Height);

	glBindVertexArray(m_companionWindow->getVAO());
	m_companionWindowShader->Bind();

	// render left eye (first half of index array )
	glBindTexture(GL_TEXTURE_2D, m_companionWindow->getLeftEyeFrameBuffer().m_nResolveTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDrawElements(GL_TRIANGLES, m_companionWindow->getIndexSize() / 2, GL_UNSIGNED_SHORT, 0);

	// render right eye (second half of index array )
	glBindTexture(GL_TEXTURE_2D, m_companionWindow->getRightEyeFrameBuffer().m_nResolveTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDrawElements(GL_TRIANGLES, m_companionWindow->getIndexSize() / 2, GL_UNSIGNED_SHORT, (const void *)(uintptr_t)(m_companionWindow->getIndexSize()));

	glBindVertexArray(0);

	m_companionWindowShader->Unbind();
}
