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


void Renderer::Render(RawModel* model)
{
	glBindVertexArray(model->GetVaoID());
	glEnableVertexAttribArray(0);

	// Draw the model
	//glDrawArrays(GL_TRIANGLES, 0, model->GetVertexCount());
	glDrawElements(GL_TRIANGLES, model->GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}