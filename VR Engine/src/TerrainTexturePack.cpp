#include "TerrainTexturePack.h"


TerrainTexturePack::TerrainTexturePack(Texture * background, Texture * r, Texture * g, Texture * b)
	:m_BackgroundTexture(background), m_RTexture(r), m_GTexture(g), m_BTexture(b)
{
}

TerrainTexturePack::~TerrainTexturePack()
{
}
