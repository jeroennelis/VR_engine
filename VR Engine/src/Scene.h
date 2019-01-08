#pragma once
#include <iostream>
#include <unordered_map>
#include "Entity.h"
#include "Loader.h"
#include "OBJLoader.h"
#include "TerrainTexturePack.h"
#include "Light.h"
#include "Terrain.h"
#include "GuiTexture.h"
#include "VRSettings.h"
#include "XYZLoader.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Move.h"
#include "Terrain.h"
#include "WaterTile.h"

class Scene
{
public:
	Scene(bool usingVR);
	~Scene();

	void Init();
	void Update();

	inline GameObject * GetLight() { return m_Light; }
	inline std::unordered_map <GLuint, std::vector<Entity*>> * GetStaticEntities() { return &m_StaticEntities; }
	inline std::vector<GameObject*> * GetTerrains() { return &m_Terrains; }
	inline VRSettings * GetVRSettings() { return &m_VRSettings; }
	inline bool IsUsingVR() { return m_UsingVR; }
	inline std::vector<GameObject*> * getGameObjects() { return &m_GameObjects; }

	inline std::vector<RawModel> * GetPointCloud() { return &m_PointClouds; }
	inline GameObject * GetCurrentCamera() { return m_CurrentCamera; }
	inline Loader * GetLoader() { return &m_Loader; }
	inline std::vector<WaterTile> GetWater() { return m_Water; }
	//inline std::vector<AnimatedModel *> & GetAnimatedModels() { return m_AnimatedModels; }
	inline std::vector<RawModel> * GetGrass() { return &m_Grass; }


	void AddGameObject(GameObject * gameObject);

private:
	Loader m_Loader;

	std::vector<Texture *> m_Textures;
	std::vector<RawModel *> m_RawModels;
	std::vector<TexturedModel *> m_TexturedModels;

	GameObject * m_Player;

	std::vector<GuiTexture *> m_Guis;

	TerrainTexturePack * m_TerrainTexturePack;

	GameObject * m_Light;

	std::unordered_map <GLuint, std::vector<Entity*>> m_StaticEntities;
	std::vector<GameObject*> m_Terrains;

	VRSettings m_VRSettings;

	bool m_UsingVR;

	std::vector<RawModel> m_PointClouds;

	std::vector<RawModel> m_Grass;

	std::vector<GameObject *> m_GameObjects;
	//std::vector<AnimatedModel *> m_AnimatedModels;

	GameObject * m_CurrentCamera;

	std::vector<WaterTile> m_Water;

private:
	void InitTerrain();
	void InitPlayer();
	void InitLights();
	void InitCam();
	void InitGuis();
	void InitPointCloud();
	void InitWater();
	void InitGameObjects();
	void AnimationTest();
	void InitGrass();

	void ProcessTerrain(GameObject * terrain);
};

