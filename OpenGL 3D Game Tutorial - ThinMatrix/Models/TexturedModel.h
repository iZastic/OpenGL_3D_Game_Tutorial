#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "../Textures/ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel& model, ModelTexture& texture, bool blendAlpha = false)
		: m_rawModel(model), m_texture(texture), m_blendAlpha(blendAlpha) {}

	inline RawModel GetRawModel() const { return m_rawModel; }
	inline ModelTexture GetModelTexture() const { return m_texture; }
	inline bool GetBlendAlpha() const { return m_blendAlpha; }
private:
	RawModel m_rawModel;
	ModelTexture m_texture;
	bool m_blendAlpha;
};

#endif // TEXTUREDMODEL_H