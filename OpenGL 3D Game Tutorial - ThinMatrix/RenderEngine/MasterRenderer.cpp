#include <glm\gtx\transform.hpp>
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(float aspectRatio)
	: m_shader(BasicShader("basicShader")), m_renderer(Renderer(m_shader))
{
	// Create the projection matrix using GLM and load it into the shader
	m_shader.Use();
	m_shader.LoadProjectionMatrix(glm::perspective(m_FOV, aspectRatio, m_NEAR_PLANE, m_FAR_PLANE));
	m_shader.UnUse();
}


MasterRenderer::~MasterRenderer()
{
}


void MasterRenderer::Render(Light& light, Camera& camera)
{
	// Clear buffers and activate the shader
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader.Use();
	// Load shader parameters
	m_shader.LoadLight(light, 0.1f);
	m_shader.LoadViewMatrix(camera);

	m_renderer.Render(m_entities);

	// Deactivate shader and clear entities
	m_shader.UnUse();
	m_entities.clear();
}

#include <iostream>
void MasterRenderer::ProcessEntity(Entity& entity)
{
	// Get the textured model
	TexturedModel& texturedModel = entity.GetModel();
	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_entities.insert(std::make_pair(texturedModel, std::vector<Entity>()));
	// Add the entity to the entities list
	m_entities.find(texturedModel)->second.push_back(entity);
}
