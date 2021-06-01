#pragma once

#include "Editor.h"
#include "Map.h"
#include "Ant.h"

class Application
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Time deltaTime;
	SimulationSettings* settings;
	Editor* editor;
	bool editorVisible;
	Map* map;

	Ant ant;

public:
	Application();
	~Application();

	void Start();
	void UpdateEvents();
	void Update();
	void Render();
};