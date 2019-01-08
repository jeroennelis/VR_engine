#pragma once
#include <unordered_map>
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "Texture.h"
#include "Entity.h"
#include "TerrainRenderer.h"
#include "Scene.h"
#include "CompanionWindow.h"
#include "VRRenderer.h"
#include "PointCloudRenderer.h"
#include "FrameBuffer.h"
#include "EditorUiRenderer.h"
#include "WaterRenderer.h"
#include "WaterFrameBuffers.h"
#include "Transform.h"
#include "SkyboxRenderer.h"
#include "GrassRenderer.h"

class MasterRenderer
{
public:
	MasterRenderer(Scene * scene);
	~MasterRenderer();
	
	void Render();

	static void EnableCulling();
	static void DisableCulling();

	static float RED;
	static float GREEN;
	static float BLUE;

private:
	Scene * m_Scene;
	VRSettings * m_VRSettings;
	EntityRenderer m_EntityRenderer;
	TerrainRenderer m_TerrainRenderer;
	WaterRenderer m_WaterRenderer;
	CompanionWindow * m_CompanionWindow;
	VRRenderer * m_VRRenderer;
	PointCloudRenderer m_PointCloudRenderer;
	FrameBuffer framebuffer;
	EditorUiRenderer m_EditorUIRenderer;
	WaterFrameBuffers m_WaterFrameBuffers;
	SkyboxRenderer m_SkyboxRenderer;
	//AnimatedEntityRenderer m_AnimatedEntityRenderer;
	GrassRenderer m_GrassRenderer;
	
	glm::mat4 m_ProjectionMatrix;
	std::unordered_map<GLuint, std::vector<Entity>> m_Entities;
	std::vector<Terrain> m_Terrains;
	void Prepare();
	void CreateProjectionMatrix();

private:
	void RenderScene();
	void RenderFrame(const glm::mat4 & viewProjectionMatrix, const glm::vec4 & clipPlane);
	void RenderVR();
	void RenderStereoTargets();
	void RenderEye(vr::Hmd_Eye nEye);
};

