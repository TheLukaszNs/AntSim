#pragma once

#include "Editor.h"
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

	Ant ant;

public:
	Application();
	~Application();

	void Start();
	void UpdateEvents();
	void Update();
	void Render();
};