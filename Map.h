#pragma once

#include "settings.h"
#include "MapGrid.h"

class Map
{
private:
	sf::RenderWindow* window;
	sf::CircleShape antHill;

	void DisplayAll();

public:
	MapGrid* grid;

	Map(sf::RenderWindow* window);
	~Map();

	void Update(const float& dt);
	void Render();
	void AddPoint(sf::Vector2f position, AntState state);

	void DrawAntHill();
};