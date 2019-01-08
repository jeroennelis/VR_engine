#pragma once
#include <iostream>
#include <vector>
#include "RawModel.h"
#include "GL.h"
#include "Texture.h"
#include "DataStructures.h"

class Loader
{
private:
	std::vector<GLuint> m_Vaos;
	std::vector<GLuint> m_Vbos;

public:
	Loader();
	~Loader();

	RawModel LoadToVAO(std::vector<float> &positions, std::vector<float> &textureCoords, std::vector<float> &normals, std::vector<int> &indices);
	RawModel LoadToVAO(std::vector<float> &positions, int dimensions);
	RawModel LoadPointCloudToVAO(std::vector<float>& positions, std::vector<float>& colours);
	RawModel LoadToVAO(MeshData &data);
	GLuint LoadCubeMap(std::vector<std::string> & textureFiles);
private:
	GLuint CreateVAO();
	void StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<float> &data);
	void StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<int> &data);
	void UnbindVAO();
	void bindIndicesBuffer(std::vector<int> & indices);
	
};

