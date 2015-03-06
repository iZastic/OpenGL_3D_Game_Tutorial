#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include <vector>
#include "../Shaders/TerrainShader.h"
#include "../Terrain/Terrain.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix);
	virtual ~TerrainRenderer();

	void Render(std::vector<Terrain>& terrains);
private:
	TerrainShader& m_shader;
	void BindTerrain(Terrain& terrain);
	void UnbindTerrain();
	void RenderTerrain(Terrain& terrain);
};

#endif // TERRAINRENDERER_H