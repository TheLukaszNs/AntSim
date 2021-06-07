#pragma once

#include "settings.h"

class Editor
{
private:
	sf::RenderWindow* window;

	void DisplaySettings();

public:
	Editor(sf::RenderWindow* window);
	~Editor();

	void ShowEditor(std::function<void(void)> OnStartSimulation);
};