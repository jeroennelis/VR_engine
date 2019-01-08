#pragma once
#include "TexturedModel.h"
#include "GLM\glm.hpp"

struct Trans {
	glm::vec3 m_Position;
	float m_RotX, m_RotY, m_RotZ;
	float m_Scale;

	Trans(glm::vec3 position, float rotx, float roty, float rotz, float scale);
};

class Entity
{

private:
	TexturedModel  * m_Model;
	Trans m_Translation;

	int m_TextureIndex = 0;

public:
	Entity(TexturedModel * model, Trans translation, int textureIndex = 0);
	~Entity();

	void IncreasePosition(float dx, float dy, float dz);
	void IncreaseRotation(float dx, float dy, float dz);
	
	//TODO const???
	inline TexturedModel * GetModel() { return m_Model; }
	inline Trans & GetTransform() { return m_Translation; }

	inline void SetModel(TexturedModel * model) { m_Model = model; }
	inline void SetTransform(Trans & translation) { m_Translation = translation; }

	float GetTextureXOffset();
	float GetTextureYOffset();
};

