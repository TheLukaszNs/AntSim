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
	Editor* editor;
	bool editorVisible;
	Map* map;

	std::vector<Ant*> ants;

public:
	Application();
	~Application();

	void Start();
	void UpdateEvents();
	void Update();
	void Render();
};