#include "pch.h"
#include "Map.h"

sf::Color Map::ConvertColor(float color[4])
{
	return sf::Color(static_cast<sf::Uint32>(color[0] * 255), static_cast<sf::Uint32>(color[1] * 255), static_cast<sf::Uint32>(color[2] * 255), 255);
}

void Map::DisplayAll()
{
	this->window->draw(this->antHill);
	
	for (int i = 0; i < this->food.size(); i++)
		this->window->draw(this->food[i]);

	for (int i = 0; i < this->walls.size(); i++)
		this->window->draw(this->walls[i]);
}

Map::Map(sf::RenderWindow* window, SimulationSettings* settings) : window(window), settings(settings)
{

}

Map::~Map()
{

}

void Map::Update()
{

}

void Map::Render()
{
	switch (this->settings->placeObject)
	{
	case 0:
		if (!this->settings->antHillPlaced)
			this->DrawAntHill();
		break;

	case 1:
		this->DrawFood();
		break;

	case 2:
		this->DrawWalls();
		break;

	default:
		break;
	}

	this->DisplayAll();
}

void Map::DrawAntHill()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	this->antHill.setRadius(25.0f);
	this->antHill.setFillColor(this->ConvertColor(this->settings->antHillColor));
	this->antHill.setPosition(sf::Vector2f(mousePosition.x - this->antHill.getRadius(), mousePosition.y - this->antHill.getRadius()));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->settings->antHillPlaced = true;

	this->window->draw(this->antHill);
}

void Map::DrawFood()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	sf::CircleShape f;
	f.setRadius(50.0f);
	f.setFillColor(this->ConvertColor(this->settings->foodColor));
	f.setPosition(sf::Vector2f(mousePosition.x - f.getRadius(), mousePosition.y - f.getRadius()));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->food.push_back(f);

	this->window->draw(f);
}

void Map::DrawWalls()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	this->w.setSize(sf::Vector2f(200.0f, 10.0f));
	this->w.setFillColor(this->ConvertColor(this->settings->wallColor));
	this->w.setPosition(sf::Vector2f(mousePosition.x - this->w.getSize().x / 2, mousePosition.y - this->w.getSize().y / 2));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		this->w.rotate(10.0f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->walls.push_back(this->w);

	this->window->draw(this->w);
}