#version 330 core

// IN variables
layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoords;
layout(location=2) in vec3 normal;

// OUT variables
out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

// Matricies
uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform float useUpNormal;

void main()
{
	// Calculate the position of the object in the world
	vec4 worldPosition = transformMatrix * vec4(position, 1.0);

	vec3 actualNormal = normal;
	if (useUpNormal == 1.0)
		actualNormal = vec3(0, 1, 0);

	// Multiply the normal by transformation matrix (fixes normal if object is rotated)
	surfaceNormal = (transformMatrix * vec4(actualNormal, 0.0)).xyz;
	// Get the vector of the light from the position the object is in the world
	toLightVector = lightPosition - worldPosition.xyz;
	// Get the vector to the camera from the position of the object
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	// Pass the texture coords to the next shader
	textureCoords = texCoords;

	// Get the final position
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
}