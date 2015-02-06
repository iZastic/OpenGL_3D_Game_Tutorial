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

GameManager::GameManager()
{
	// Initialized GLFW
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// Set minimum OpenGL version and options
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);

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

	// START temporary model data
	float vertices[] = {
		// Front face
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,

		// Back face
		-1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, -1.0, -1.0,

		// Top face
		-1.0, 1.0, -1.0,
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, -1.0,

		// Bottom face
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, 1.0,
		-1.0, -1.0, 1.0,

		// Right face
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, 1.0, 1.0,
		1.0, -1.0, 1.0,

		// Left face
		-1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, 1.0, -1.0
	};

	int indices[] = {
		0, 1, 2, 0, 2, 3,    // front
		4, 5, 6, 4, 6, 7,    // back
		8, 9, 10, 8, 10, 11,   // top
		12, 13, 14, 12, 14, 15,   // bottom
		16, 17, 18, 16, 18, 19,   // right
		20, 21, 22, 20, 22, 23    // left
	};

	float texCoords[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	RawModel model = loader.LoadToVAO(vertices, indices, texCoords,
		sizeof(vertices) / sizeof(vertices[0]),
		sizeof(indices) / sizeof(indices[0]),
		sizeof(texCoords) / sizeof(texCoords[0]));
	ModelTexture texture(loader.LoadTexture("image"));
	TexturedModel texturedModel(model, texture);

	Entity entity(texturedModel, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	// END temporary model data

	Camera camera;

	float x = -0.001f;
	// Start the game loop
	while (m_displayManager->IsWindowOpen())
	{
		// Rotate cube
		entity.ChangeRotation(glm::vec3(0.001f, 0.001f, 0.001f));
		camera.Move();
		renderer.Prepare();
		staticShader.Use();
		staticShader.LoadViewMatrix(camera);
		renderer.Render(entity, staticShader);
		staticShader.UnUse();

		m_displayManager->UpdateDisplay();
	}
}
