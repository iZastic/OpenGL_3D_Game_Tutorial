#include <iostream>
#include "DisplayManager.h"

DisplayManager::DisplayManager(int width, int height, const std::string& title)
{
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
	glfwDestroyWindow(m_window);
}


bool DisplayManager::IsWindowOpen()
{
	return !glfwWindowShouldClose(m_window);
}


void DisplayManager::UpdateDisplay()
{
	// Tell GLFW to get window events
	glfwPollEvents();
	// Tell GLFW to swap buffers
	glfwSwapBuffers(m_window);
}