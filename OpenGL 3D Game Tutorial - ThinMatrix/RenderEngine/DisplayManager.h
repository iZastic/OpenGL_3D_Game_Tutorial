#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <string>
#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	DisplayManager(int width = 800, int height = 600, const std::string& title = "OpenGL Window");
	virtual ~DisplayManager();

	bool IsWindowOpen();
	void UpdateDisplay();
private:
	GLFWwindow* m_window;
};

#endif // DISPLAYMANAGER_H