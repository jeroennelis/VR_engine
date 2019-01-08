#include <iostream>
#include <string>
#include <gl/glew.h>
#include "Window.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "MasterRenderer.h"
#include "Terrain.h"
#include "TerrainTexturePack.h"
#include "ModelTexture.h"
#include "GuiTexture.h"
#include "GuiRenderer.h"
#include "VRSettings.h"
#include "Scene.h"
#include "XYZLoader.h"
#include "FrameBuffer.h"
#include "Transform.h"
#include "MeshRenderer.h"

int main(void)
{
	//ColladaLoader::LoadColladaModel("res/animations/model.dae", 3);
	



	bool uhd = false;

	std::string title = "test";
	int width = 1920;
	int height = 1080;
	

	if (uhd)
	{
		height *= 2;
		width *= 2;
	}

	Window window(width, height, title);
	window.Init();
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window.GetWindow(), true);

	bool usingVR = false;
	Scene scene(usingVR);
	scene.Init();	

	MasterRenderer masterRenderer(&scene);
	glEnable(GL_PROGRAM_POINT_SIZE);
	{
		while (!glfwWindowShouldClose(window.GetWindow()))
		{
			scene.Update();
			glfwPollEvents();
			glEnable(GL_CLIP_DISTANCE0);
			masterRenderer.Render();
			
			window.Update();
		}
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
glfwTerminate();
}