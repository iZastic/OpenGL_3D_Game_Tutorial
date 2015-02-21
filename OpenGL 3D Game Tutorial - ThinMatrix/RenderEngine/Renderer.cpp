#include "Renderer.h"
#include <GL\glew.h>
#include <glm\gtx\transform.hpp>
#include "../Toolbox/Maths.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"

Renderer::Renderer(StaticShader& shader, float& aspect)
{
	// Don't draw faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Tell OpenGL to test for depth
	glEnable(GL_DEPTH_TEST);
	// Set clear color and clear the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);


	// Create the projection matrix using GLM
	m_projectionMatrix = glm::perspective(m_FOV, aspect, m_NEAR_PLANE, m_FAR_PLANE);
	// Load the projection matrix into the shader
	shader.Use();
	shader.LoadProjectionMatrix(m_projectionMatrix);
	shader.UnUse();
}


Renderer::~Renderer()
{
}


void Renderer::Prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Render(Entity& entity, StaticShader& shader)
{
	TexturedModel& texturedModel = entity.GetModel();
	// Get the RawModel from the textured model
	RawModel& model = texturedModel.GetRawModel();
	// Bind the models VAO
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);

	// Load the transformation matrix into the shader
	shader.LoadTransformMatrix(Maths::CreateTransformMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Load shine from the texture
	ModelTexture texture = texturedModel.GetModelTexture();
	shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());

	// Activate an OpenGL texture and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.GetModelTexture().GetTextureID());
	// Draw the model
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);

	// Disable the attrib arrays
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}