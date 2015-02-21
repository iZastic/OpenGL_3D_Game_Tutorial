#version 330 core

in vec2 textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 fragColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main()
{
	// Normalize the vectors
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	// Find out how close the face is to facing the light
	float howBright = dot(unitNormal, unitLightVector);
	// Make sure the brightness is above 0
	float brightness = max(howBright, 0.0);
	// Get the ammount of light color to add
	vec3 diffuse = brightness * lightColor;

	// Output the texture color plus the ammount of light color
	fragColor = vec4(diffuse, 1.0) * texture(textureSampler, textureCoords);
}