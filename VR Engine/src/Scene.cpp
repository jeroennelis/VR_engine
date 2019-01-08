#include "Scene.h"



Scene::Scene(bool usingVR)
	:m_UsingVR(usingVR)
{
	if (usingVR)
		m_VRSettings.Init();
}


Scene::~Scene()
{
	for (Texture * texture : m_Textures)
		delete texture;
	for (RawModel * rawModel : m_RawModels)
		delete rawModel;
	for (TexturedModel * texturedModel : m_TexturedModels)
		delete texturedModel;

	delete m_Player;

	for (GuiTexture * guiTexture : m_Guis)
		delete guiTexture;

	delete m_TerrainTexturePack;
	delete m_Light;
}

void Scene::Init()
{
	InitTerrain();
	InitPlayer();
	InitLights();
	InitCam();
	InitWater();
	//InitGameObjects();
	InitGrass();
	AnimationTest();
}

void Scene::Update()
{
	for (GameObject *gameObject : m_GameObjects)
		gameObject->Update();
	/*for (AnimatedModel * model : m_AnimatedModels)
		model->Update();*/
}

void Scene::AddGameObject(GameObject * gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void Scene::InitTerrain()
{
	Texture * backgroundTexture = new Texture("res/textures/grassy.png");
	m_Textures.push_back(backgroundTexture);
	Texture * rTexture = new Texture("res/textures/mud.png");
	m_Textures.push_back(rTexture);
	Texture * gTexture = new Texture("res/textures/pinkFlowers.png");
	m_Textures.push_back(gTexture);
	Texture * bTexture = new Texture("res/textures/path.png");
	m_Textures.push_back(bTexture);
	Texture * blendMap = new Texture("res/textures/newBlend.png");
	m_Textures.push_back(blendMap);

	m_TerrainTexturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
	Component * terrainComponent = new Terrain(0, -1, m_Loader, "res/textures/heightmap.png", m_TerrainTexturePack, blendMap);
	GameObject * terrain = new GameObject("Terrain");
	AddGameObject(terrain);
	terrain->AddComponent(terrainComponent);
	ProcessTerrain(terrain);
}

void Scene::InitPlayer()
{
	RawModel * model = new RawModel(OBJLoader::loadOBJModel("res/models/character.obj", m_Loader));
	ModelTexture * texture = new ModelTexture("res/textures/white.png");
	TexturedModel * texturedModel = new TexturedModel(model, texture);
	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetModel(texturedModel);

	GameObject * player = new GameObject("player");
	player->AddComponent(meshRenderer);
	AddGameObject(player);
	m_Player = player;

	Move * move = new Move(player->GetComponent<Transform>(), m_Terrains[0]->GetComponent<Terrain>());
	player->AddComponent(move);
	player->GetComponent<Transform>()->Position.z = -150;

}

void Scene::InitLights()
{
	GameObject * light = new GameObject("Light");
	Component * lightComponent = new Light();
	light->AddComponent(lightComponent);
	AddGameObject(light);
	m_Light = light;
	m_Light->GetComponent<Transform>()->Position = glm::vec3(0, 21, -150);
}

void Scene::InitCam()
{
	GameObject * cameraObject = new GameObject("camera");
	Camera * camera = new Camera(cameraObject->GetComponent<Transform>());
	cameraObject->AddComponent(camera);
	
	AddGameObject(cameraObject);
	m_CurrentCamera = cameraObject;
	camera->SetPlayerTransform(m_Player->GetComponent<Transform>());
}

void Scene::InitGuis()
{
	GuiTexture * gui = new GuiTexture("res/textures/fern.png", glm::vec2(0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
	m_Guis.push_back(gui);
}

void Scene::InitPointCloud()
{
	m_PointClouds = XYZLoader::LoadXYZModel("res/models/oude statie.xyz",m_Loader);
	//m_PointClouds.push_back(OBJLoader::loadOBJModelPointCloud("res/models/lichaam.obj", m_Loader));
}

void Scene::InitWater()
{
	m_Water.push_back(WaterTile{ 200,-200,-19 });
}

void Scene::InitGameObjects()
{
	GameObject * huis = new GameObject("huis");
	RawModel * model = new RawModel(OBJLoader::loadOBJModel("res/models/huis.obj", m_Loader));
	ModelTexture * texture = new ModelTexture("res/textures/huis.png");
	TexturedModel * texturedModel = new TexturedModel(model, texture);
	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetModel(texturedModel);
	huis->AddComponent(meshRenderer);
	m_GameObjects.push_back(huis);

	huis->GetComponent<Transform>()->Position.z = -150;
	huis->GetComponent<Transform>()->Position.y = 19.80;
	huis->GetComponent<Transform>()->Rotation.y = 180;

	GameObject * body = new GameObject("huis");
	RawModel * model2 = new RawModel(OBJLoader::loadOBJModel("res/models/character.obj", m_Loader));
	ModelTexture * texture2 = new ModelTexture("res/textures/character.png");
	TexturedModel * texturedModel2 = new TexturedModel(model2, texture2);
	MeshRenderer * meshRenderer2 = new MeshRenderer();
	meshRenderer2->SetModel(texturedModel2);
	body->AddComponent(meshRenderer2);
	m_GameObjects.push_back(body);

	body->GetComponent<Transform>()->Position.z = -150;
	body->GetComponent<Transform>()->Position.y = 19.95;
	body->GetComponent<Transform>()->Rotation.y = 180;
	body->GetComponent<Transform>()->Rotation.x = 90;
}

void Scene::AnimationTest()
{
	/*GameObject * animatedModel = new GameObject("animated model");
	AnimatedModelData modelData = ColladaLoader::LoadColladaModel("res/animations/model.dae", 3);
	RawModel * model = new RawModel(m_Loader.LoadToVAO(modelData.Mesh.Vertices, modelData.Mesh.TextureCoords, modelData.Mesh.Normals, modelData.Mesh.Indices));
	ModelTexture * texture = new ModelTexture("res/textures/diffuse.png");
	TexturedModel * texturedModel = new TexturedModel(model, texture);
	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetModel(texturedModel);
	animatedModel->AddComponent(meshRenderer);
	m_GameObjects.push_back(animatedModel);

	animatedModel->GetComponent<Transform>()->Position.z = -100;
	animatedModel->GetComponent<Transform>()->Position.y = 5.5;*/

	/*AnimatedModel * thinMatrix = new AnimatedModel(AnimatedModelLoader::LoadEntity("res/animations/model.dae", "res/textures/diffuse.png"));
	Animation * animation = new Animation( AnimationLoader::LoadAnimation("res/animations/model.dae"));
	thinMatrix->DoAnimation(animation);
	m_AnimatedModels.emplace_back(thinMatrix);*/
	

}

void Scene::InitGrass()
{
	std::vector<float> vertices;


	for (float x = 0; x < 100; x++)
	{
		for (float z = 0; z > -100; z--)
		{
			float y = m_Terrains[0]->GetComponent<Terrain>()->GetHeightOfTerrain(x, z);
			std::cout << y << std::endl;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	RawModel model = m_Loader.LoadToVAO(vertices, 3);
	m_Grass.push_back(model);
}

void Scene::ProcessTerrain(GameObject * terrain)
{
	m_Terrains.push_back(terrain);
}


