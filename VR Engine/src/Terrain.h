#pragma once
#include <iostream>
#include <vector>
#include <GLM\glm.hpp>

#include "Loader.h"
#include "RawModel.h"
#include "TerrainTexturePack.h"
#include "Maths.h"


class Terrain: public Component
{
private:
	const float SIZE;
	const float MAX_HEIGHT;
	const float MAX_PIXEL_COLOUR;

	float m_X;
	float m_Z;
	RawModel m_Model;
	TerrainTexturePack * m_TexturePack;
	Texture * m_BlendMap;

	std::vector<std::vector<float>> m_Heights;

public:
	Terrain(int gridX, int gridZ, Loader & loader, const std::string & heightMap, TerrainTexturePack * texturePack, Texture * blendMap);
	~Terrain();

	// Inherited via Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void ShowInpectorInfo() override;

	float GetHeightOfTerrain(float worldX, float worldZ);

	inline float GetX() const { return m_X; }
	inline float GetZ() const { return m_Z; }

	inline RawModel * GetRawModel() { return &m_Model; }
	inline TerrainTexturePack * GetTexturePack() { return m_TexturePack; }
	inline Texture * GetBlendMap() { return m_BlendMap; }


private:
	RawModel GenerateTerrain(Loader & loader, const std::string & heightMap);
	float GetHeigt(int x, int y, unsigned char* localBuffer, int height);
	glm::vec3 CalculateNormal(int x, int y, unsigned char* localBuffer, int height);

	
	
};

