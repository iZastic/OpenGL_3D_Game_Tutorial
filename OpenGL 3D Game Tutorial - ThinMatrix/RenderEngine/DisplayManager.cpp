#include <iostream>
#include "DisplayManager.h"

DisplayManager::DisplayManager(int width, int height, const std::string& title)
{
	m_title = title;
	m_aspect = (float)width / (float)height;

	// Set minimum OpenGL version and options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create OpenGL window using GLFW
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	// Check if window was created
	if (m_window != NULL)
	{
		std::cout << "Window created successfully" << std::endl;
		// Set OpenGL context to the window
		glfwMakeContextCurrent(m_window);
		// Set OpenGL viewport to full size of the window
		glViewport(0, 0, width, height);
		// Enable vertical sync
		glfwSwapInterval(1);
	}
	else
	{
		std::cerr << "ERROR: Failed to create window" << std::endl;
	}
}


DisplayManager::~DisplayManager()
{
	std::cout << "Window destroyed" << std::endl;
	glfwDestroyWindow(m_window);
}


bool DisplayManager::IsWindowOpen()
{
	return !glfwWindowShouldClose(m_window);
}


void DisplayManager::UpdateDisplay()
{
	// Tell GLFW to swap buffers
	glfwSwapBuffers(m_window);
	// Tell GLFW to get window events
	glfwPollEvents();
}


float& DisplayManager::GetAspect()
{
	return m_aspect;
}

void DisplayManager::ShowUPS()
{
	// Static variables are only initialized once ever
	// Used for the size of the average array
	const static int SIZE = 500;
	// Array used to store every frames render time
	static double avgList[SIZE] = { 0.0 };
	// Variables to computer frame render time
	static double previous = 0.0;
	double now = glfwGetTime();
	double average = 0.0;

	// Move every value in the list forward, value position 1 is now in position 0
	for (unsigned int i = 0; i < SIZE - 1; i++)
	{
		avgList[i] = avgList[i + 1];
		average += avgList[i];
	}
	// Store the new time in the last slot
	avgList[SIZE - 1] = now - previous;
	// Add the new time to the average
	average += avgList[SIZE - 1];
	// Divide average my the array size to get the average time
	average /= SIZE;

	// Update the title with the FPS
	glfwSetWindowTitle(m_window, (m_title + " | FPS: " + std::to_string(1.0f / average)).c_str());

	// Store the current time
	previous = now;
}