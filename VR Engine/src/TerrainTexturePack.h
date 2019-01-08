#pragma once
#include "Texture.h"

class TerrainTexturePack
{
private:
	Texture * m_BackgroundTexture;
	Texture * m_RTexture;
	Texture * m_GTexture;
	Texture * m_BTexture;


public:
	TerrainTexturePack(Texture * background, Texture * r, Texture * g, Texture * b);
	~TerrainTexturePack();

	inline Texture * GetBackgroundTexture() { return m_BackgroundTexture; }
	inline Texture * GetRTexture() { return m_RTexture; }
	inline Texture * GetGTexture() { return m_GTexture; }
	inline Texture * GetBTexture() { return m_BTexture; }
};

