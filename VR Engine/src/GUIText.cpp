#include "GUIText.h"

#include "FontType.h"

GUIText::GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered)
	:TextString(text), FontSize(FontSize), Font(font), Position(position), LineMaxSize(maxLineLength), CenterText(centered)
{
}

void GUIText::SetMeshInfo(int vao, int verticesCount)
{
}

void GUIText::SetColour(float r, float g, float b)
{
	Colour = glm::vec3(r, g, b);
}
