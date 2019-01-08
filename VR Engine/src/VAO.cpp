#include "VAO.h"


VAO::VAO(int id)
	:m_RendererID(id)
{
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
	for (GLuint vboID : m_VBOs)
	{
		GLCall(glDeleteBuffers(1, &vboID));
	}
}

VAO VAO::Create()
{
	GLuint id;
	GLCall(glGenVertexArrays(1, &id));
	return VAO(id);
}

void VAO::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VAO::StoreIndicesInAtributeList(std::vector<int> & indices)
{
	if (!indices.size())
	{
		std::cout << "empty index buffer!!!" << std::endl;
		return;
	}
	GLuint vboID;
	GLCall(glGenBuffers(1, &vboID));
	m_VBOs.push_back(vboID);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW));

}

void VAO::StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
{
	if (!data.size())
	{
		std::cout << "empty buffer!!!" << std::endl;
		return;
	}
	GLuint vboID;
	GLCall(glGenBuffers(1, &vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW));  // TODO spec size of float
	GLCall(glEnableVertexAttribArray(attributeNumber));
	GLCall(glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	m_VBOs.push_back(vboID);

}

void VAO::StoreDataInAtributeList(int attributeNumber, int coordinateSize, std::vector<int>& data)
{
	if (!data.size())
	{
		std::cout << "empty buffer!!!" << std::endl;
		return;
	}
	GLuint vboID;
	GLCall(glGenBuffers(1, &vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(int), &data.front(), GL_STATIC_DRAW));  // TODO spec size of int
	GLCall(glEnableVertexAttribArray(attributeNumber));
	GLCall(glVertexAttribIPointer(attributeNumber, coordinateSize, GL_INT, 0, 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	m_VBOs.push_back(vboID);
}


