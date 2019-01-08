#include "TexturedModel.h"



TexturedModel::TexturedModel(RawModel  *model, ModelTexture  *texture)
	:m_RawModel(model), m_Texture(texture)
{
}

TexturedModel::~TexturedModel()
{
	//delete m_RawModel;
	//delete m_Texture;
}
