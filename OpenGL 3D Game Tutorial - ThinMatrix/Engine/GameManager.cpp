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
#include "../Entities/FPSCamera.h"
#include "../RenderEngine/OBJLoader.h"
#include "../Terrain/Terrain.h"

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

	srand(time(0));
	std::vector<Entity> entities;

	RawModel mBox = OBJLoader::LoadObjModel("lowPolyTree", loader);
	ModelTexture mtBox(loader.LoadTexture("lowPolyTree"));
	TexturedModel tmBox(mBox, mtBox);
	for (int i = 0; i < 25; i++){
		int x = rand() % 500 - 250;
		int z = rand() % 500 - 250;
		entities.push_back(Entity(tmBox, glm::vec3(x, 0, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	}

	RawModel mGrass = OBJLoader::LoadObjModel("grass", loader);
	ModelTexture mtGrass(loader.LoadTexture("grass"), true, true);
	TexturedModel tmGrass(mGrass, mtGrass);
	for (int i = 0; i < 100; i++){
		int x = rand() % 500 - 250;
		int z = rand() % 500 - 250;
		entities.push_back(Entity(tmGrass, glm::vec3(x, 0, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	}

	RawModel mFern = OBJLoader::LoadObjModel("fern", loader);
	ModelTexture mtFern1(loader.LoadTexture("fern1"), true, true);
	ModelTexture mtFern2(loader.LoadTexture("fern2"), true, true);
	ModelTexture mtFern3(loader.LoadTexture("fern3"), true, true);
	ModelTexture mtFern4(loader.LoadTexture("fern4"), true, true);
	TexturedModel tmFern1(mFern, mtFern1);
	TexturedModel tmFern2(mFern, mtFern2);
	TexturedModel tmFern3(mFern, mtFern3);
	TexturedModel tmFern4(mFern, mtFern4);
	for (int i = 0; i < 20; i++){
		int x = rand() % 200 - 100;
		int z = rand() % 200 - 100;
		entities.push_back(Entity(i < 5 ? tmFern1 : i < 10 ? tmFern2 : i < 15 ? tmFern3 : tmFern4, glm::vec3(x, 0, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	}


	std::vector<Terrain> terrains;
	terrains.push_back(Terrain(-1, 0, loader, ModelTexture(loader.LoadTexture("grassy3", true))));
	terrains.push_back(Terrain(0, 0, loader, ModelTexture(loader.LoadTexture("grassy2", true))));
	terrains.push_back(Terrain(-1, -1, loader, ModelTexture(loader.LoadTexture("grassy2", true))));
	terrains.push_back(Terrain(0, -1, loader, ModelTexture(loader.LoadTexture("grassy3", true))));

	Light light(glm::vec3(0, 50, 0), glm::vec3(1, 1, 1));
	FPSCamera camera(true);
	// END temporary data

	MasterRenderer renderer(m_displayManager->GetAspect());
	// Start the game loop
	while (m_displayManager->IsWindowOpen())
	{
		camera.Update();

		for (Terrain& t : terrains)
			renderer.ProcessTerrain(t);
		for (Entity& e : entities)
			renderer.ProcessEntity(e);

		renderer.Render(light, camera.GetViewMatrix());

		m_displayManager->UpdateDisplay();
		m_displayManager->ShowUPS();
	}
}
