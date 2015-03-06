#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../RenderEngine/Loader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader& loader, ModelTexture t);
	virtual ~Terrain();

	inline float GetX() { return m_x; }
	inline float GetZ() { return m_z; }
	inline RawModel GetModel() { return m_model; }
	inline ModelTexture GetTexture() { return m_texture; }
private:
	const float SIZE = 800;
	const int VERTEX_COUNT = 128;
	float m_x, m_z;
	RawModel m_model;
	ModelTexture m_texture;
	RawModel GenerateTerrain(Loader& loader);
};

#endif // TERRAIN_H