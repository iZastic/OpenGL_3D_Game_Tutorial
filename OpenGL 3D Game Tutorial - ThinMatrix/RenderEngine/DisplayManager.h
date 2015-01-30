#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <string>
#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	DisplayManager(int width, int height, const std::string& title);
	virtual ~DisplayManager();

	bool IsWindowOpen();
	void UpdateDisplay();
private:
	GLFWwindow* m_window;
};

#endif // DISPLAYMANAGER_H