#include "WaterRenderer.h"



WaterRenderer::WaterRenderer(Loader * loader, WaterFrameBuffers * fbos)
	:m_Shader("res/shaders/Water.shader"), m_fbos(fbos)
{
	dudvTexture = new Texture("res/textures/waterDUDV.png");
	normalTexture = new Texture("res/textures/normalMap.png");
	m_Shader.Bind();
	m_Shader.ConnectTextureUnits();
	m_Shader.Unbind();
	SetUpVAO(loader);
}

WaterRenderer::~WaterRenderer()
{
	delete dudvTexture;
	delete normalTexture;
}

void WaterRenderer::LoadProjectionMatrix(glm::mat4 & projectionMatrix)
{
	m_Shader.Bind();
	m_Shader.LoadProjectionMatrix(projectionMatrix);
	m_Shader.Unbind();
}

void WaterRenderer::SetUpVAO(Loader * loader)
{
	std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
	m_Quad = loader->LoadToVAO(vertices, 2);
}

void WaterRenderer::Render(std::vector<WaterTile> water, GameObject * camera, GameObject * light)
{
	prepareRender(camera, light);
	for (WaterTile tile : water) {
		Trans transform(glm::vec3(tile.X, tile.Height, tile.Z), 0, 0, 0, tile.TILE_SIZE);
		glm::mat4 modelMatrix = Maths::CreateTransformationMatrix(transform);
		m_Shader.LoadTransformationMatrix(modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, m_Quad.vertexCount);
	}
	unbind();
}

void WaterRenderer::prepareRender(GameObject *  camera, GameObject * light) {
	m_Shader.Bind();
	m_Shader.LoadViewMatrix(camera);
	moveFactor += WAVE_SPEED;
	moveFactor = fmod(moveFactor, 1);
	m_Shader.LoadMoveFactor(moveFactor);
	glm::vec3 pos= light->GetComponent<Transform>()->Position;
	m_Shader.LoadLight(light);
	glBindVertexArray(m_Quad.vaoID);
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbos->GetReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_fbos->GetRefractionTexture());
	dudvTexture->Bind(2);
	normalTexture->Bind(3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_fbos->GetRefractionDepthTexture());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void WaterRenderer::unbind() {
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_Shader.Unbind();
}