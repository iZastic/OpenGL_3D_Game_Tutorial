#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <GL\glew.h>
#include "GameManager.h"
#include "../RenderEngine/Loader.h"
#include "../RenderEngine/MasterRenderer.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"
#include "../Textures/ModelTexture.h"
#include "../Shaders/BasicShader.h"
#include "../Entities/Entity.h"
#include "../Entities/Camera.h"
#include "../RenderEngine/OBJLoader.h"

GameManager::GameManager()
{
	// Initialized GLFW
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;

		// Create the display manager (pointers must be deleted)
		m_displayManager = new DisplayManager(1280, 720, "ThinMatrix OpenGL Game");

		// Initialize glew using experimental(new)
		glewExperimental = true;
		GLenum status = glewInit();
		if (status == GLEW_OK)
		{
			std::cout << "GLEW initialized successfully" << std::endl;
		}
		else
		{
			std::cerr << "ERROR: GLEW failed to initialize \n" << glewGetErrorString(status) << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: GLFW failed to initialize" << std::endl;
	}
}


GameManager::~GameManager()
{
	// Delete the display and clean up GLFW
	delete m_displayManager;
	glfwTerminate();
}

void GameManager::Start()
{
	std::cout << "Game loop is now running" << std::endl;

	// START temporary data
	Loader loader;
	std::string object = "box";
	RawModel model = OBJLoader::LoadObjModel(object, loader);
	ModelTexture texture(loader.LoadTexture(object));
	texture.SetShineDamper(10);
	texture.SetShine(1);
	TexturedModel texturedModel(model, texture);

	srand(time(0));
	std::vector<Entity> entities;
	for (int i = 0; i < 10; i++){
		int x = rand() % 20 - 20;
		int y = rand() % 20;
		int z = rand() % 20 - 20;
		entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	}
	// END temporary data

	Light light(glm::vec3(0, 10, 0), glm::vec3(1, 1, 1));
	Camera camera;

	float x = 0.002f;
	MasterRenderer renderer(m_displayManager->GetAspect());
	// Start the game loop
	while (m_displayManager->IsWindowOpen())
	{
		camera.Move();

		for (Entity& e : entities)
		{
			e.ChangeRotation(glm::vec3(x * ((rand() % 8 + 2) / 2), x * ((rand() % 8 + 2) / 2), 0));
			renderer.ProcessEntity(e);
		}
		renderer.Render(light, camera);

		m_displayManager->UpdateDisplay();
		m_displayManager->ShowUPS();
	}
}
