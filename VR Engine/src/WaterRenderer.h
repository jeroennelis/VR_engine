#pragma once
#include "RawModel.h"
#include "WaterShader.h"
#include "Loader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "Texture.h"

#define WAVE_SPEED 0.003f

class WaterRenderer
{
public:
	WaterRenderer(Loader * loader, WaterFrameBuffers * fbos);
	~WaterRenderer();

	void Render(std::vector<WaterTile> water, GameObject * camera, GameObject * light);
	void SetUpVAO(Loader * loader);
	


	void LoadProjectionMatrix(glm::mat4 & projectionMatrix);

private:
	RawModel m_Quad;
	WaterShader m_Shader;
	WaterFrameBuffers * m_fbos;
	Texture * dudvTexture;
	Texture * normalTexture;

	float moveFactor = 0;

	void prepareRender(GameObject *  camera, GameObject * light);
	void unbind();


};
