#include "TerrainShader.h"
#include "../Toolbox/Maths.h"

TerrainShader::TerrainShader()
	: ShaderProgram("../res/shaders/terrainShader")
{
	BindAttributes();
	GetAllUniformLocations();
}


TerrainShader::~TerrainShader()
{
}


void TerrainShader::LoadTransformMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_TransformMatrix, matrix);
}


void TerrainShader::LoadProjectionMatrix(glm::mat4& matrix)
{
	LoadMatrix4(location_ProjectionMatrix, matrix);
}


void TerrainShader::LoadViewMatrix(glm::mat4& cameraViewMatrix)
{
	LoadMatrix4(location_ViewMatrix, cameraViewMatrix);
}


void TerrainShader::LoadLight(Light& light, float ambientLight)
{
	LoadVector(location_lightPosition, light.GetPosition());
	LoadVector(location_lightColor, light.GetColor());
	LoadFloat(location_ambientLight, ambientLight);
}


void TerrainShader::LoadShineVariables(float shineDamper, float shine)
{
	LoadFloat(location_shineDamper, shineDamper);
	LoadFloat(location_shine, shine);
}


void TerrainShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "texCoords");
	BindAttribute(2, "normal");
}


void TerrainShader::GetAllUniformLocations()
{
	location_TransformMatrix = GetUniformLocation("transformMatrix");
	location_ProjectionMatrix = GetUniformLocation("projectionMatrix");
	location_ViewMatrix = GetUniformLocation("viewMatrix");
	location_lightPosition = GetUniformLocation("lightPosition");
	location_lightColor = GetUniformLocation("lightColor");
	location_ambientLight = GetUniformLocation("ambientLight");
	location_shineDamper = GetUniformLocation("shineDamper");
	location_shine = GetUniformLocation("shine");
}