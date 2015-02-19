#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <string>
#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	DisplayManager();
	DisplayManager(int width, int height, const std::string& title);
	virtual ~DisplayManager();

	bool IsWindowOpen();
	void UpdateDisplay();
	float& GetAspect();
	void ShowUPS();
private:
	GLFWwindow* m_window;
	float m_aspect;
	std::string m_title;
};

#endif // DISPLAYMANAGER_H