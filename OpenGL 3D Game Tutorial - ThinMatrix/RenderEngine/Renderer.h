#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>
#include "../Entities/Entity.h"
#include "../Shaders/BasicShader.h"

struct tmCompare
{
public:
	bool operator() (const TexturedModel& t1, const TexturedModel& t2)
	{
		return &t1 == &t2;
	}
};

class Renderer
{
public:
	Renderer(BasicShader& shader);
	virtual ~Renderer();

	void Render(std::map<TexturedModel, std::vector<Entity>, tmCompare>& entities);
private:
	BasicShader& m_shader;
	void BindTexturedModel(TexturedModel texturedModel);
	void UnbindTexturedModel();
	void RenderEntity(Entity& entity);
};

#endif // RENDERER_H