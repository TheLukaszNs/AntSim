#pragma once

#include "settings.h"

class Map
{
private:
	sf::RenderWindow* window;
	SimulationSettings* settings;
	sf::CircleShape antHill;
	std::vector<sf::CircleShape> food;
	std::vector<sf::RectangleShape> walls;
	sf::RectangleShape w;

	sf::Color ConvertColor(float color[4]);
	void DisplayAll();

public:
	Map(sf::RenderWindow* window, SimulationSettings* settings);
	~Map();

	void Update();
	void Render();

	void DrawAntHill();
	void DrawFood();
	void DrawWalls();
};