#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../RenderEngine/DisplayManager.h"

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	void Start();
private:
	DisplayManager* m_displayManager;
};

#endif // GAMEMANAGER_H