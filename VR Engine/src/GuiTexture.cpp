#include "GuiTexture.h"



GuiTexture::GuiTexture(const std::string & path, glm::vec2 position, glm::vec2 scale)
	:Texture(path), m_Position(position), m_Scale(scale)
{
}

GuiTexture::GuiTexture(int textureID, glm::vec2 position, glm::vec2 scale)
	: Texture(textureID), m_Position(position), m_Scale(scale)
{
}

GuiTexture::~GuiTexture()
{
}
