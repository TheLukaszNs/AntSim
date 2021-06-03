#pragma once

#include "Map.h"

enum class AntState
{
	Searching, Returning
};

class Ant
{
private:
	AntState state = AntState::Searching;
	
	sf::CircleShape shape;
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f direction;

	Map* map;

	float accumulatedTime{};

public:
	Ant(Map* map);
	~Ant();
	void Wander(const float& dt);

	void HandleFood();
	void Update(const float& dt);
	void Render(sf::RenderWindow* window);
};

