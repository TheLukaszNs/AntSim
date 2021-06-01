#pragma once

#include "settings.h"

class Editor
{
private:
	sf::RenderWindow* window;
	SimulationSettings* settings;

	void DisplaySettings();

public:
	Editor(sf::RenderWindow* window, SimulationSettings* settings);
	~Editor();

	void ShowEditor();
};