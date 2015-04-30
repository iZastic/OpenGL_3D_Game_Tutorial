#include "BasicShader.h"
#include "../Toolbox/Maths.h"

BasicShader::BasicShader()
	: ShaderProgram("../res/shaders/basicShader")
{
	BindAttributes();
	GetAllUniformLocations();
}


BasicShader::~BasicShader()
{
}


void BasicShader::LoadTransformMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_TransformMatrix, matrix);
}


void BasicShader::LoadProjectionMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_ProjectionMatrix, matrix);
}


void BasicShader::LoadViewMatrix(glm::mat4& cameraViewMatrix)
{
	LoadMatrix4(location_ViewMatrix, cameraViewMatrix);
}


void BasicShader::LoadLight(Light& light, float ambientLight)
{
	LoadVector(location_lightPosition, light.GetPosition());
	LoadVector(location_lightColor, light.GetColor());
	LoadFloat(location_ambientLight, ambientLight);
}


void BasicShader::LoadShineVariables(float shineDamper, float shine)
{
	LoadFloat(location_shineDamper, shineDamper);
	LoadFloat(location_shine, shine);
}


void BasicShader::LoadUseUpNormal(bool useUpNormal)
{
	LoadBool(location_useUpNormal, useUpNormal);
}


void BasicShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "texCoords");
	BindAttribute(2, "normal");
}


void BasicShader::GetAllUniformLocations()
{
	location_TransformMatrix = GetUniformLocation("transformMatrix");
	location_ProjectionMatrix = GetUniformLocation("projectionMatrix");
	location_ViewMatrix = GetUniformLocation("viewMatrix");
	location_lightPosition = GetUniformLocation("lightPosition");
	location_lightColor = GetUniformLocation("lightColor");
	location_ambientLight = GetUniformLocation("ambientLight");
	location_shineDamper = GetUniformLocation("shineDamper");
	location_shine = GetUniformLocation("shine");
	location_useUpNormal = GetUniformLocation("useUpNormal");
}