#include <GL\glew.h>
#include "../Toolbox/Maths.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"
#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(BasicShader& shader, glm::mat4& projectionMatrix) : m_shader(shader)
{
	// Load the projection matrix into the shader
	m_shader.Use();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.UnUse();
}


EntityRenderer::~EntityRenderer()
{
}

#include <iostream>
void EntityRenderer::Render(std::map<TexturedModel, std::vector<Entity>, tmCompare>& entities, glm::vec3 cameraPos)
{
	std::multimap<float, Entity> transparentEntities;

	// Loop through the keys
	// key.first = Textured model, key.second = entities vector
	for (auto &key : entities)
	{
		// If TexturedModel needs alpha blend (example: a windows glass), Save it for rendering last
		if (key.first.GetBlendAlpha())
		{
			for (Entity e : key.second)
			{
				// They need to be orded by distance, so we add them to the map by distance from the camera
				float distance = glm::length(cameraPos - e.GetPosition());
				transparentEntities.insert(std::make_pair(distance, e));
			}
			continue;
		}
		BindTexturedModel(key.first);
		for (Entity entity : key.second)
			RenderEntity(entity);
		UnbindTexturedModel();
	}

	// They need to be draw from farthest to nearest, so we draw them in reverse order by distance
	for (std::map<float, Entity>::reverse_iterator it = transparentEntities.rbegin(); it != transparentEntities.rend(); ++it)
	{
		BindTexturedModel(it->second.GetModel());
		RenderEntity(it->second);
		UnbindTexturedModel();
	}
}


void EntityRenderer::BindTexturedModel(TexturedModel texturedModel)
{
	// Get the RawModel from the textured model
	RawModel& model = texturedModel.GetRawModel();
	// Bind the models VAO
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);
	// Load shine from the texture
	ModelTexture texture = texturedModel.GetModelTexture();
	// Disable cullinging if back faces might be seen due to transparency
	if (texture.GetHasTransparency())
		glDisable(GL_CULL_FACE);
	// Load using the fake UP normal bool
	m_shader.LoadUseUpNormal(texture.GetUseUpNormal());
	// Load shineness
	m_shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());
	// Activate an OpenGL texture and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.GetModelTexture().GetTextureID());
}


void EntityRenderer::UnbindTexturedModel()
{
	// Re-enable culling if disabled
	glEnable(GL_CULL_FACE);
	// Disable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}


void EntityRenderer::RenderEntity(Entity& entity)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformMatrix(Maths::CreateTransformMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetModel().GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
