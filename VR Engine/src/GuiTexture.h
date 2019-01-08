#pragma once
#include "Texture.h"
#include "GLM\glm.hpp"

class GuiTexture :
	public Texture
{
private:
	glm::vec2 m_Position;
	glm::vec2 m_Scale;

public:
	GuiTexture(const std::string& path, glm::vec2 position, glm::vec2 scale);
	GuiTexture(int textureID, glm::vec2 position, glm::vec2 scale);
	~GuiTexture();

	inline glm::vec2 GetPosition() const { return m_Position; }
	inline glm::vec2 GetScale() const { return m_Scale; }
};

