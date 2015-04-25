#include "Maths.h"
#include <glm\gtx\transform.hpp>

glm::mat4 Maths::CreateTransformMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
{
	// Create transformation matrix
	glm::mat4 transMatrix = glm::translate(translation);
	// Create rotation matrix
	glm::mat4 rotMatrix =
		glm::rotate(rotation.z, glm::vec3(0, 0, 1)) *
		glm::rotate(rotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	// Create scale matrix
	glm::mat4 scaleMatrix = glm::scale(scale);

	// Return total transform matrix
	return transMatrix * rotMatrix * scaleMatrix;
}