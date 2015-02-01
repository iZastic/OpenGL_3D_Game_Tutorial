#version 330

in vec3 position;
in vec2 texCoords;

out vec2 textureCoords;

uniform mat4 transformMatrix;

void main()
{
	gl_Position = transformMatrix * vec4(position, 1.0);

	textureCoords = texCoords;
}