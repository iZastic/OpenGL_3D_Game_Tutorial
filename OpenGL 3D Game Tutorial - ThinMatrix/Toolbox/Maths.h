#ifndef MATHS_H
#define MATHS_H

#include <glm\glm.hpp>
#include "../Entities/Camera.h"

class Maths
{
public:
	static glm::mat4 CreateTransformMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
};

#endif // MATHS_H