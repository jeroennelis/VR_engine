#include "GuiRenderer.h"



GuiRenderer::GuiRenderer(Loader & loader)
	:quad(loader.LoadToVAO(m_Positions, 2)), m_Shader("res/shaders/Gui.shader")
{
}


GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::Render(std::vector<GuiTexture>& guis)
{
	m_Shader.Bind();
	GLCall(glBindVertexArray(quad.vaoID));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glDisable(GL_DEPTH_TEST));
	for (GuiTexture & gui : guis)
	{
		gui.Bind();
		glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(gui.GetPosition(), gui.GetScale());
		m_Shader.LoadTransformationMatrix(transformationMatrix);
		GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.vertexCount));
	}
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDisable(GL_BLEND));
	GLCall(glBindVertexArray(0));
	m_Shader.Unbind();
}
