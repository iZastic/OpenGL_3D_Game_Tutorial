#ifndef RENDERER_H
#define RENDERER_H

#include <glm\glm.hpp>
#include "../Entities/Entity.h"
#include "../Shaders/StaticShader.h"

class Renderer
{
public:
	Renderer(StaticShader& shader, float& aspect);
	virtual ~Renderer();

	void Prepare();
	void Render(Entity& entity, StaticShader& shader);
private:
	const float m_FOV = 70;
	const float m_NEAR_PLANE = 0.1f;
	const float m_FAR_PLANE = 1000;
	glm::mat4 m_projectionMatrix;
};

#endif // RENDERER_H