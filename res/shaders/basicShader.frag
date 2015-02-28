#version 330 core

in vec2 textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 fragColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float ambientLight;
uniform float shineDamper;
uniform float shine;

void main()
{
	// Normalize the vectors
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	/* Used for diffuse lighting */
	// Find out how bright the light should be and keep it above 0
	float brightness = dot(unitNormal, unitLightVector);
	brightness = max(brightness, ambientLight);
	// Get the ammount of light color to add
	vec3 diffuse = brightness * lightColor;

	/* Used for specular lighting */
	vec3 unitCameraVector = normalize(toCameraVector);
	// Get the direction the light is pointing
	vec3 lightDirection = -unitLightVector;
	// Get the reflection direction of the light
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	// Find out how bright the reflected light should be and keep it above 0
	float specularFactor = dot(reflectedLightDirection, unitCameraVector);
	specularFactor = max(specularFactor, 0.0);
	// Apply the specular damper and compute the final value
	float dampedSpecular = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedSpecular * shine * lightColor;

	// Output the texture color * the ammount of light color + the reflected light
	fragColor = vec4(diffuse, 1.0) * texture(textureSampler, textureCoords) + vec4(finalSpecular, 1.0);
}