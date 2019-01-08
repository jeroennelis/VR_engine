#include "Loader.h"



Loader::Loader()
{
}

Loader::~Loader()
{
	unsigned int i;
	for (i = 0; i < m_Vaos.size(); i++)
	{
		GLCall(glDeleteVertexArrays(1, &m_Vaos[i]));
	}
	for (i = 0; i < m_Vaos.size(); i++)
	{
		GLCall(glDeleteBuffers(1, &m_Vbos[i]));
	}
}

RawModel Loader::LoadToVAO(std::vector<float> &positions, std::vector<float> &textureCoords, std::vector<float> &normals, std::vector<int> &indices)
{
	GLuint vaoID = CreateVAO();
	bindIndicesBuffer(indices);
	StoreDataInAtributeList(0, 3, positions);
	StoreDataInAtributeList(1, 2, textureCoords);
	StoreDataInAtributeList(2, 3, normals);
	UnbindVAO();
	return RawModel{ vaoID, (int)indices.size() };
}



RawModel Loader::LoadToVAO(std::vector<float>& positions, int dimensions)
{
	GLuint vaoID = CreateVAO();
	StoreDataInAtributeList(0, dimensions, positions);
	UnbindVAO();
	return RawModel{ vaoID, (int)(positions.size() / dimensions) };
}

RawModel Loader::LoadPointCloudToVAO(std::vector<float>& positions, std::vector<float>& colours)
{
	GLuint vaoID = CreateVAO();
	StoreDataInAtributeList(0, 3, positions);
	StoreDataInAtributeList(1, 3, colours);
	UnbindVAO();
	return RawModel{ vaoID, (int)(positions.size() / 3) };
}

RawModel Loader::LoadToVAO(MeshData & data)
{
	GLuint vaoID = CreateVAO();
	bindIndicesBuffer(data.Indices);
	StoreDataInAtributeList(0, 3, data.Vertices);
	StoreDataInAtributeList(1, 2, data.TextureCoords);
	StoreDataInAtributeList(2, 3, data.Normals);
	StoreDataInAtributeList(3, 3, data.JointIDs);
	StoreDataInAtributeList(4, 3, data.VertexWeights);
	
	return RawModel{ vaoID, (int)data.Indices.size() };
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	GLCall(glGenVertexArrays(1, &vaoID));
	m_Vaos.push_back(vaoID);
	GLCall(glBindVertexArray(vaoID));
	return vaoID;
}

void Loader::StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<float> &data)
{
	if (data.size())
	{
		GLuint vboID;
		GLCall(glGenBuffers(1, &vboID));
		m_Vbos.push_back(vboID);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(attributeNumber));
		GLCall(glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}

void Loader::StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<int> &data)
{
	if (data.size())
	{
		GLuint vboID;
		GLCall(glGenBuffers(1, &vboID));
		m_Vbos.push_back(vboID);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(int), &data.front(), GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(attributeNumber));
		GLCall(glVertexAttribIPointer(attributeNumber, coordinateSize, GL_INT, 0, 0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}

void Loader::UnbindVAO()
{
	GLCall(glBindVertexArray(0));
}

void Loader::bindIndicesBuffer(std::vector<int> & indices)
{
	GLuint vboID;
	GLCall(glGenBuffers(1, &vboID));
	m_Vbos.push_back(vboID);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW));
}

GLuint Loader::LoadCubeMap(std::vector<std::string> & textureFiles)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	for (int i = 0; i < textureFiles.size(); i++)
	{
		stbi_set_flip_vertically_on_load(0);
		int width;
		int height;
		int BPP;
		unsigned char* buffer = stbi_load(textureFiles[i].c_str(), &width, &height, &BPP, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		if (buffer)
			stbi_image_free(buffer);
		//TODO clean up 
	}
	return texID;
}
