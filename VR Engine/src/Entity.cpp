#include "Entity.h"

Entity::Entity(TexturedModel * model, Trans translation, int textureIndex)
	:m_Model(model), m_Translation(translation), m_TextureIndex(textureIndex)
{
}

Entity::~Entity()
{
}

void Entity::IncreasePosition(float dx, float dy, float dz)
{
	m_Translation.m_Position.x += dx;
	m_Translation.m_Position.y += dy;
	m_Translation.m_Position.z += dz;
}

void Entity::IncreaseRotation(float dx, float dy, float dz)
{
	m_Translation.m_RotX += dx;
	m_Translation.m_RotY += dy;
	m_Translation.m_RotZ += dz;
}

float Entity::GetTextureXOffset()
{
	int nrOfRows = m_Model->GetTexture()->GetNrOfRows();
	int column = m_TextureIndex % nrOfRows;
	return (float)column / (float)nrOfRows;
}

float Entity::GetTextureYOffset()
{
	int nrOfRows = m_Model->GetTexture()->GetNrOfRows();
	int row = m_TextureIndex / nrOfRows;
	return (float)row / (float)nrOfRows;
}

Trans::Trans(glm::vec3 position, float rotx, float roty, float rotz, float scale)
	:m_Position(position)
{
	m_RotX = rotx;
	m_RotY = roty;
	m_RotZ = rotz;
	m_Scale = scale;
}
