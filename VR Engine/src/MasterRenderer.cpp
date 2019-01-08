#include "MasterRenderer.h"

float MasterRenderer::RED = 0.5f;
float MasterRenderer::GREEN = 0.5f;
float MasterRenderer::BLUE = 0.5f;

MasterRenderer::MasterRenderer(Scene * scene)
	:m_Scene(scene), m_VRSettings(scene->GetVRSettings()) , m_EntityRenderer(), m_TerrainRenderer(), m_WaterRenderer(scene->GetLoader(), &m_WaterFrameBuffers), m_SkyboxRenderer(scene->GetLoader())
{
	EnableCulling();
	CreateProjectionMatrix();
	
	if (m_Scene->IsUsingVR())
	{
		m_CompanionWindow = new CompanionWindow(*m_VRSettings->GetIVRSystem());
		m_VRRenderer = new VRRenderer(m_CompanionWindow);
	}
}


MasterRenderer::~MasterRenderer()
{
	delete m_CompanionWindow;
	delete m_VRRenderer;
}

void MasterRenderer::Render()
{
	if (m_Scene->IsUsingVR())
		RenderVR();
	else
	{
		CreateProjectionMatrix();

		//Render reflection texture
		// TODO check if water exists
		float waterHeight = m_Scene->GetWater()[0].Height;
		float pitch = m_Scene->GetCurrentCamera()->GetComponent<Camera>()->Pitch;
		m_WaterFrameBuffers.BindReflectionFrameBuffer();
		Prepare();
		Transform * cameraTransform = m_Scene->GetCurrentCamera()->GetComponent<Transform>();
		float distance = 2 * (cameraTransform->Position.y - waterHeight);
		cameraTransform->Position.y -= (distance);
		m_Scene->GetCurrentCamera()->GetComponent<Camera>()->Pitch -= (2* pitch);
		RenderFrame(glm::mat4(), glm::vec4(0, 1, 0, -waterHeight));
		cameraTransform->Position.y += (distance);
		m_Scene->GetCurrentCamera()->GetComponent<Camera>()->Pitch = pitch;

		//Render refraction texture
		m_WaterFrameBuffers.BindRefractionFrameBuffer();
		Prepare();
		glm::mat4 test = glm::mat4();
		RenderFrame(glm::mat4(), glm::vec4(0, -1, 0, waterHeight + 1));
		
		m_WaterFrameBuffers.UnbindCurrentFrameBuffer();

		framebuffer.Bind();
		Prepare();
		RenderFrame(glm::mat4(), glm::vec4(0, 0, 0, 0));
		m_WaterRenderer.Render(m_Scene->GetWater(), m_Scene->GetCurrentCamera(), m_Scene->GetLight());
		framebuffer.Unbind();

		Prepare();
		m_EditorUIRenderer.Render(framebuffer, m_Scene);
	}
	
}

void MasterRenderer::RenderScene()
{
	Prepare();
	RenderFrame(glm::mat4(), glm::vec4(0,-1,0,15));
}

void MasterRenderer::RenderFrame(const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane)
{
	m_EntityRenderer.Render(m_Scene, viewProjectionMatrix, clipPlane);

	m_TerrainRenderer.Render(m_Scene, viewProjectionMatrix, clipPlane);

	m_SkyboxRenderer.Render(m_Scene->GetCurrentCamera());

	//m_PointCloudRenderer.Render(m_Scene, viewProjectionMatrix);

	//m_AnimatedEntityRenderer.Render(*m_Scene, viewProjectionMatrix, clipPlane);	

	m_GrassRenderer.Render(m_Scene, viewProjectionMatrix);
}

void MasterRenderer::RenderVR()
{
	if (m_VRSettings->GetIVRSystem())
	{
		RenderStereoTargets();

		vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)m_CompanionWindow->getLeftEyeFrameBuffer().m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
		vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)m_CompanionWindow->getRightEyeFrameBuffer().m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

		m_VRRenderer->renderCompanionWindow();
	}

	// TODO, via update method of action listener
	m_VRSettings->UpdateHMDMatrixPose();
}

void MasterRenderer::RenderStereoTargets()
{
	//glClearColor(0.85f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_MULTISAMPLE);

	// Left Eye
	glBindFramebuffer(GL_FRAMEBUFFER, m_CompanionWindow->getLeftEyeFrameBuffer().m_nRenderFramebufferId);
	glViewport(0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight());
	RenderEye(vr::Eye_Left);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_MULTISAMPLE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_CompanionWindow->getLeftEyeFrameBuffer().m_nRenderFramebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_CompanionWindow->getLeftEyeFrameBuffer().m_nResolveFramebufferId);

	glBlitFramebuffer(0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight(),
		0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight(),
		GL_COLOR_BUFFER_BIT,
		GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glEnable(GL_MULTISAMPLE);

	// Right Eye
	glBindFramebuffer(GL_FRAMEBUFFER, m_CompanionWindow->getRightEyeFrameBuffer().m_nRenderFramebufferId);
	glViewport(0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight());
	RenderEye(vr::Eye_Right);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_MULTISAMPLE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_CompanionWindow->getRightEyeFrameBuffer().m_nRenderFramebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_CompanionWindow->getRightEyeFrameBuffer().m_nResolveFramebufferId);

	glBlitFramebuffer(0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight(),
		0, 0, m_CompanionWindow->getRenderWidth(), m_CompanionWindow->getRenderHeight(),
		GL_COLOR_BUFFER_BIT,
		GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void MasterRenderer::RenderEye(vr::Hmd_Eye nEye)
{
	Prepare();

	//render the scene
	RenderFrame(m_VRSettings->GetCurrentViewProjectionMatrix(nEye), glm::vec4(0,0,0,0));				//TODO

	// ----- Render Model rendering -----

	m_VRRenderer->renderVRModels(*m_VRSettings, nEye);
}

void MasterRenderer::EnableCulling()
{
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
}

void MasterRenderer::DisableCulling()
{
	GLCall(glDisable(GL_CULL_FACE));
}

void MasterRenderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	GLCall(glClearColor(RED, GREEN, BLUE, 1.0));

}

void MasterRenderer::CreateProjectionMatrix()
{
	Camera * camera = m_Scene->GetCurrentCamera()->GetComponent<Camera>();
	float aspectRatio = (float)Window::Width / (float)Window::Height;
	float y_scale = (float)((1.0f / glm::tan(glm::radians(camera->FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = camera->FAR - camera->NEAR;

	m_ProjectionMatrix = glm::mat4();
	m_ProjectionMatrix[0][0] = x_scale;
	m_ProjectionMatrix[1][1] = y_scale;
	m_ProjectionMatrix[2][2] = -((camera->FAR + camera->NEAR) / frustum_length);
	m_ProjectionMatrix[2][3] = -1;
	m_ProjectionMatrix[3][2] = -((2 * camera->NEAR * camera->FAR) / frustum_length);
	m_ProjectionMatrix[3][3] = 0;

	m_EntityRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
	m_TerrainRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
	m_PointCloudRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
	m_WaterRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
	m_SkyboxRenderer.LoadProjectioMatrix(m_ProjectionMatrix);
	//m_AnimatedEntityRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
	m_GrassRenderer.LoadProjectionMatrix(m_ProjectionMatrix);
}