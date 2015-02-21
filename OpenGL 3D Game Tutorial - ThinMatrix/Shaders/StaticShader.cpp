#include "StaticShader.h"
#include "../Toolbox/Maths.h"

StaticShader::StaticShader(const std::string& fileName)
	: ShaderProgram("../res/shaders/" + fileName)
{
	BindAttributes();
	GetAllUniformLocations();
}


StaticShader::~StaticShader()
{
}


void StaticShader::LoadTransformMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_TransformMatrix, matrix);
}


void StaticShader::LoadProjectionMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_ProjectionMatrix, matrix);
}


void StaticShader::LoadViewMatrix(Camera& camera)
{
	LoadMatrix4(location_ViewMatrix, Maths::CreateViewMatrix(camera));
}


void StaticShader::LoadLight(Light& light)
{
	LoadVector(location_lightPosition, light.GetPosition());
	LoadVector(location_lightColor, light.GetColor());
}


void StaticShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "texCoords");
	BindAttribute(2, "normal");
}


void StaticShader::GetAllUniformLocations()
{
	location_TransformMatrix = GetUniformLocation("transformMatrix");
	location_ProjectionMatrix = GetUniformLocation("projectionMatrix");
	location_ViewMatrix = GetUniformLocation("viewMatrix");
	location_lightPosition = GetUniformLocation("lightPosition");
	location_lightColor = GetUniformLocation("lightColor");
}