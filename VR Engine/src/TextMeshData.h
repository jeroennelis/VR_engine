#pragma once
#include <iostream>
#include <vector>

class TextMeshData
{
public:
	std::vector<float> VertexPositions;
	std::vector<float> textureCoords;

public:
	TextMeshData();
	~TextMeshData();
};

