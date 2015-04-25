#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include <glm\glm.hpp>

class FPSCamera
{
public:
	FPSCamera(bool freeRoam = false);
	virtual ~FPSCamera();

	void Update();
	glm::mat4 GetViewMatrix() const;

	inline glm::vec3 GetPosition() { return m_position; }
private:
	const glm::vec3 m_UP = glm::vec3(0, 1, 0);
	const float m_SENSITIVITY = 0.005f;
	const float m_SPEED = 0.5f;
	bool m_freeRoam;
	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	glm::vec2 m_mousePosition;

	void MouseUpdate(const glm::vec2 mousePosition);
	void Move();
};

#endif // FPSCAMERA_H