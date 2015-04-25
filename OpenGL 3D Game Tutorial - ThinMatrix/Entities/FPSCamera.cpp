#include "FPSCamera.h"
#include <GLFW\glfw3.h>
#include <glm\gtx\transform.hpp>

FPSCamera::FPSCamera(bool freeRoam)
	: m_position(0, 5, 0), m_viewDirection(0, 0, -1), m_freeRoam(freeRoam)
{
	// Hide the cursor
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


FPSCamera::~FPSCamera()
{
}

void FPSCamera::Update()
{
	// Get the mouse X and Y and update camera view
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	MouseUpdate(glm::vec2(x, y));

	Move();
}


glm::mat4 FPSCamera::GetViewMatrix() const
{
	// Create the view matrix with camera values
	return glm::lookAt(m_position, m_position + m_viewDirection, m_UP);
}


void FPSCamera::MouseUpdate(const glm::vec2 mousePosition)
{
	// Get distance and direction the mouse moved
	glm::vec2 mouseDelta = mousePosition - m_mousePosition;

	// If for some reason the mouse jumps a distance greater than 100, ignore it
	if (glm::length(mouseDelta) > 100)
	{
		m_mousePosition = mousePosition;
		return;
	}

	// Find the vector to rotate around vertically
	glm::vec3 vAxis = glm::cross(m_viewDirection, m_UP);

	// (Horizontal) Rotate around the UP axis using the distance the mouse moved in the X axis
	// (Vertical) Rotate around the vAxis using the distance the mouse moved in the Y axis
	// Then apply these rotations to the view direction and normalize
	m_viewDirection = glm::normalize(glm::mat3(
		glm::rotate(-mouseDelta.x * m_SENSITIVITY, m_UP) *
		glm::rotate(-mouseDelta.y * m_SENSITIVITY, vAxis)
		) * m_viewDirection);

	// Update the mouse position
	m_mousePosition = mousePosition;
}

void FPSCamera::Move()
{
	float multiplier = 1;
	// Hold shift to move faster
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		multiplier = 10;
	// 4 movement directions
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_position += -m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_position += -m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_position += m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier;
	// Press escape to exit
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
}