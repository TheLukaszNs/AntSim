#pragma once
class Ant
{
private:
	sf::CircleShape shape;
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f direction;

	float accumulatedTime{};

public:
	Ant();
	~Ant();
	void Wander(const float& dt);

	void Update(const float& dt);
	void Render(sf::RenderWindow* window);
};

