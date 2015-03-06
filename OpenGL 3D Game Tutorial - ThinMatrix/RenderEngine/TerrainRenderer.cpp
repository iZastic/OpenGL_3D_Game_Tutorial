#include "TerrainRenderer.h"
#include "../Toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Load the projection matrix into the shader
	m_shader.Use();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.UnUse();
}


TerrainRenderer::~TerrainRenderer()
{
}


void TerrainRenderer::Render(std::vector<Terrain>& terrains)
{
	for (Terrain& terrain : terrains)
	{
		BindTerrain(terrain);
		RenderTerrain(terrain);
		UnbindTerrain();
	}
}


void TerrainRenderer::BindTerrain(Terrain& terrain)
{
	// Get the RawModel from the textured model
	RawModel& model = terrain.GetModel();
	// Bind the models VAO
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);
	// Load shine from the texture
	ModelTexture texture = terrain.GetTexture();
	m_shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());
	// Activate an OpenGL texture and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
}


void TerrainRenderer::UnbindTerrain()
{
	// Disable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}


void TerrainRenderer::RenderTerrain(Terrain& terrain)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformMatrix(Maths::CreateTransformMatrix(glm::vec3(terrain.GetX(), 0, terrain.GetZ()), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	// Draw the model
	glDrawElements(GL_TRIANGLES, terrain.GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
