#include "TexturedModel.h"


TexturedModel::TexturedModel(RawModel model, ModelTexture texture)
	: m_rawModel(model), m_texture(texture)
{
}


TexturedModel::~TexturedModel()
{
}


RawModel TexturedModel::GetRawModel()
{
	return m_rawModel;
}


ModelTexture TexturedModel::GetModelTexture()
{
	return m_texture;
}