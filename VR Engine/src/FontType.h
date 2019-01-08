#pragma once
#include <iostream>

#include "TextMeshCreator.h"
#include "TextMeshData.h"

class GUIText;

class FontType
{
private:
	int m_TextureAtlas;
	TextMeshCreator m_loader;

public:
	FontType(int textureAtlas, const std::string & path);
	~FontType();

	TextMeshData LoadText(GUIText text);
};

