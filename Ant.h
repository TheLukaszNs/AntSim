#pragma once

#include "AntState.h"
#include "Map.h"



class Ant
{
private:
	AntState state = AntState::Searching;
	
	sf::CircleShape shape;
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f direction;

	sf::Vector2f prevPos;

	Map* map;

	float accumulatedTime{};
	float speed = 100.f;

public:
	Ant(Map* map);
	~Ant();
	void Wander(const float& dt);

	void HandleFood();
	bool CheckBoundaries();
	void GetBestMove();
	void Update(const float& dt);
	void Render(sf::RenderWindow* window);
};

