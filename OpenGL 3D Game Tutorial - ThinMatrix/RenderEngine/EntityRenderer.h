#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>
#include "../Entities/Entity.h"
#include "../Shaders/BasicShader.h"

// This struct is used to compare entities in a map
struct tmCompare
{
public:
	bool operator() (const TexturedModel& t1, const TexturedModel& t2)
	{
		return &t1 == &t2;
	}
};

class EntityRenderer
{
public:
	EntityRenderer(BasicShader& shader, glm::mat4& projectionMatrix);
	virtual ~EntityRenderer();

	void Render(std::map<TexturedModel, std::vector<Entity>, tmCompare>& entities);
private:
	BasicShader& m_shader;
	void BindTexturedModel(TexturedModel texturedModel);
	void UnbindTexturedModel();
	void RenderEntity(Entity& entity);
};

#endif // RENDERER_H