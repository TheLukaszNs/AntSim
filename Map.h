#pragma once

#include "settings.h"
#include "MapGrid.h"

enum class MapPointType
{
	Neutral, Food, 
};

struct MapPoint
{
	sf::Vector2f pos;

	MapPointType type = MapPointType::Neutral;
	float pheromone[2] = { 0.f, 0.f };
};

class Map
{
private:
	sf::RenderWindow* window;
	sf::CircleShape antHill;
	std::vector<sf::CircleShape> food;
	std::vector<sf::RectangleShape> walls;
	sf::RectangleShape w;
	std::vector<MapPoint*> points;
	std::vector<sf::Vertex> verticesToDraw;

	MapGrid* grid;

	sf::Color ConvertColor(float color[4]);
	void DisplayAll();

public:

	
	Map(sf::RenderWindow* window);
	~Map();

	void Update(const float& dt);
	void Render();
	void AddPoint(sf::Vector2f position);

	MapPoint* GetPointInsideCircle(sf::Vector2f pos, float radius);
	MapPoint* GetFoodInsideCircle(sf::Vector2f pos, float radius);

	void DrawAntHill();
	void DrawFood();
	void DrawWalls();
};