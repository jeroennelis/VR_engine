#pragma once
#include <iostream>
#include <GLM\glm.hpp>

#include "FontType.h"

struct GUIText
{
	std::string TextString;
	float FontSize;

	int TextMeshVao;
	int VertexCount;
	glm::vec3 Colour = glm::vec3(0,0,0);

	glm::vec2 Position;
	float LineMaxSize;
	int NumberOfLInes;

	FontType Font;
	bool CenterText = false;

	GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered);

	void SetMeshInfo(int vao, int verticesCount);
	void SetColour(float r, float g, float b);
};
