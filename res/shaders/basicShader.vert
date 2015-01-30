#version 330

in vec3 position;

out vec3 color;

void main()
{
	gl_Position = vec4(position, 1.0);

	color = vec3(position.x + 0.5, 1.0, position.y + 0.5);
}