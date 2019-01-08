#pragma once
#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
private:
	RawModel* m_RawModel;
	ModelTexture* m_Texture;

public:
	TexturedModel(RawModel *model, ModelTexture *texture);
	~TexturedModel();

	inline RawModel *GetRawModel() const { return m_RawModel; }
	inline ModelTexture *GetTexture() const { return m_Texture; }
};

