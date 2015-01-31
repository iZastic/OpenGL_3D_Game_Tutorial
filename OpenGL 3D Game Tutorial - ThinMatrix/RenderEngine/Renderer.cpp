#include "Renderer.h"
#include <GL\glew.h>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::Prepare()
{
	// Set clear color and clear the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Render(TexturedModel* texturedModel)
{
	// Get the RawModel from the textured model
	RawModel model = texturedModel->GetRawModel();
	// Bind the models VAO
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Activate an OpenGL texture and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel->GetModelTexture().GetTextureID());
	// Draw the model
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);

	// Disable the attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}