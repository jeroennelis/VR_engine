#pragma once

#include "GL.h"
#include "VBO.h"
#include "VertexBufferLayout.h"

class VAO
{
private:
	
	std::vector<GLuint> m_VBOs;
	GLuint m_IndexVBO;

	VAO(int id);
public:
	
	GLuint m_RendererID;
	int m_IndexCount;

	~VAO();
	static VAO Create();


	void Bind()const;
	void Unbind()const;


	void StoreIndicesInAtributeList(std::vector<int> & indices);
	void StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<float> &data);
	void StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<int> &data);

	
};

