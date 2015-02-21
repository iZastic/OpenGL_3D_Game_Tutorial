#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>

class Light
{
public:
	Light(glm::vec3 p, glm::vec3 c) : m_position(p), m_color(c) {}

	inline glm::vec3 GetPosition() {
		return m_position;
	}
	inline void SetPosition(glm::vec3 p) {
		m_position = p;
	}
	inline glm::vec3 GetColor() {
		return m_color;
	}
	inline void SetColor(glm::vec3 c) {
		m_color = c;
	}
private:
	glm::vec3 m_position;
	glm::vec3 m_color;
};

#endif // LIGHT_H