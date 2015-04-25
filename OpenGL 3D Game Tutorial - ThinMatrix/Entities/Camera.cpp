#include "Camera.h"
#include <GLFW\glfw3.h>
#include <glm\gtx\transform.hpp>

Camera::Camera()
	: m_position(glm::vec3(0, 5, 0))
{
	
}


Camera::~Camera()
{
}


void Camera::Update()
{
	float speed = 0.25f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed *= 10;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_position.z -= speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_position.z += speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_position.x -= speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_position.x += speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
		m_position.y += speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
		m_position.y -= speed;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F6) == GLFW_PRESS)
	{
		if (m_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		m_wireframe = !m_wireframe;
	}
}


glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}