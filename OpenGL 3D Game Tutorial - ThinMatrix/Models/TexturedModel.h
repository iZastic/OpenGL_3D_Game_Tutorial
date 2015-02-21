#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "../Textures/ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel& model, ModelTexture& texture) : m_rawModel(model), m_texture(texture) {}

	inline RawModel GetRawModel() { return m_rawModel; }
	inline ModelTexture GetModelTexture() { return m_texture; }
private:
	RawModel m_rawModel;
	ModelTexture m_texture;
};

#endif // TEXTUREDMODEL_H