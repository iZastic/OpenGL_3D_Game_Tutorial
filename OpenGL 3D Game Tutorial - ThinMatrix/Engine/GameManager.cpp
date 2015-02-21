#include <iostream>
#include <GL\glew.h>
#include "GameManager.h"
#include "../RenderEngine/Loader.h"
#include "../RenderEngine/Renderer.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"
#include "../Textures/ModelTexture.h"
#include "../Shaders/StaticShader.h"
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

	Loader loader;

	StaticShader staticShader("basicShader");

	Renderer renderer(staticShader, m_displayManager->GetAspect());

	// START temporary data
	std::string object = "dragon";
	RawModel model = OBJLoader::LoadObjModel(object, loader);
	ModelTexture texture(loader.LoadTexture(object));
	texture.SetShineDamper(10);
	texture.SetShine(1);
	TexturedModel texturedModel(model, texture);

	Entity entity(texturedModel, glm::vec3(0, 0, -25), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	
	Light light(glm::vec3(0, 30, 0), glm::vec3(1, 1, 1));
	// END temporary data
	
	Camera camera;

	float x = 0.002f;
	// Start the game loop
	while (m_displayManager->IsWindowOpen())
	{
		// Rotate cube
		entity.ChangeRotation(glm::vec3(0, x, 0));
		camera.Move();
		renderer.Prepare();
		staticShader.Use();
		staticShader.LoadViewMatrix(camera);
		staticShader.LoadLight(light);
		renderer.Render(entity, staticShader);
		staticShader.UnUse();

		m_displayManager->UpdateDisplay();
		m_displayManager->ShowUPS();
	}
}
