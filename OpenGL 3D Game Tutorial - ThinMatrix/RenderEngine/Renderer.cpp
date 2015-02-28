#include "Renderer.h"
#include <GL\glew.h>
#include "../Toolbox/Maths.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"

Renderer::Renderer(BasicShader& shader) : m_shader(shader)
{
	// Don't draw faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Tell OpenGL to test for depth
	glEnable(GL_DEPTH_TEST);
	// Set clear color and clear the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
}


Renderer::~Renderer()
{
}


void Renderer::Render(std::map<TexturedModel, std::vector<Entity>, tmCompare>& entities)
{
	// Loop through the keys
	for (auto &key : entities)
	{
		// key.first = Textured model, key.second = entities vector
		BindTexturedModel(key.first);
		for (Entity entity : key.second)
			RenderEntity(entity);
		UnbindTexturedModel();
	}
}


void Renderer::BindTexturedModel(TexturedModel texturedModel)
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
	m_shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());
	// Activate an OpenGL texture and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.GetModelTexture().GetTextureID());
}


void Renderer::UnbindTexturedModel()
{
	// Disable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}


void Renderer::RenderEntity(Entity& entity)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformMatrix(Maths::CreateTransformMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetModel().GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
