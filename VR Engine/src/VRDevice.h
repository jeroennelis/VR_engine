#pragma once

#include <iostream>
#include <openvr.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>


class VRDevice
{
public:
	VRDevice(const std::string & sRenderModelName);
	~VRDevice();

	bool Init(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture);
	void Cleanup();
	void Draw();
	const std::string & GetName() const { return m_modelName; }
	const char getDevClassChar() const { return m_DevClassChar; }
	const bool isVisible() const { return m_visible; }

	inline void setTexture(GLuint textureCoord) { m_texture = textureCoord; }
	inline void setVertArray(GLuint vertexArray) { m_vertexArray = vertexArray; }
	inline void setVertexCount(GLsizei vertexCount) { m_vertexCount = vertexCount; }
	inline void setVisible(bool visible) { m_visible = visible; }

	inline const glm::mat4 getHmdMatrix() { return m_matrix; }
	inline void setHmdMatrix(glm::mat4 matrix) { m_matrix = matrix; }

private:
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	GLuint m_vertexArray;
	GLuint m_texture;
	GLsizei m_vertexCount;
	std::string m_modelName;

	bool m_visible;

	char m_DevClassChar;

	glm::mat4 m_matrix;
};

