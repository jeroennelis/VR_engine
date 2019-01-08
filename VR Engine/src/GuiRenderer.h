#pragma once
#include "RawModel.h"
#include "Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"
#include "Maths.h"

class GuiRenderer
{
private:
	
	std::vector<float> m_Positions = { -1, 1, -1, -1 ,1 ,1 ,1 ,-1 };
	const RawModel quad;
	GuiShader m_Shader;

public:
	GuiRenderer(Loader & loader);
	~GuiRenderer();

	void Render(std::vector<GuiTexture> & guis);
};

