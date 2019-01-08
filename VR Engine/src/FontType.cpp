#include "FontType.h"

#include "GUIText.h"

FontType::FontType(int textureAtlas, const std::string & path)
	:m_TextureAtlas(textureAtlas), m_loader(path)
{
}

FontType::~FontType()
{
}

TextMeshData FontType::LoadText(GUIText text)
{
	//TODO
	return TextMeshData();
}
