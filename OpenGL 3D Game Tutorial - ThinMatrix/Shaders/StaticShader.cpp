#include "StaticShader.h"

StaticShader::StaticShader(const std::string& fileName)
	: ShaderProgram("../res/shaders/" + fileName)
{

}


StaticShader::~StaticShader()
{
}


void StaticShader::LoadTransformMatrix(glm::mat4 matrix)
{
	LoadMatrix4(location_TransformMatrix, matrix);
}


void StaticShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "texCoords");
}


void StaticShader::GetAllUniformLocations()
{
	location_TransformMatrix = GetUniformLocation("transformMatrix");
}