#include "Camera.h"
#include <GLFW\glfw3.h>

Camera::Camera()
	: m_position(glm::vec3(0, 0, 0))
{
	
}


Camera::~Camera()
{
}


void Camera::Move()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_position.z -= 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_position.z += 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_position.x -= 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_position.x += 0.002f;
}