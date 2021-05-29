#pragma once

#include "Editor.h"

class Application
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Time deltaTime;
	Editor* editor;
	bool editorVisible;

public:
	Application();
	~Application();

	void Start();
	void UpdateEvents();
	void Update();
	void Render();
};