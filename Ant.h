#pragma once
class Ant
{
private:
	sf::CircleShape shape;
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f direction;

public:
	Ant();
	~Ant();

	void Update(const float& dt);
	void Render(sf::RenderWindow* window);
};

