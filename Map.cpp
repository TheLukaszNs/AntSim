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

Map::Map(sf::RenderWindow* window) : window(window)
{
	grid = new MapGrid(window->getSize().x, window->getSize().y, 10);
}

Map::~Map()
{

}

void Map::Update(const float& dt)
{
	grid->Update(dt);
}

void Map::Render()
{
	grid->Render(window);

	
	if(!verticesToDraw.empty())
	{
		window->draw(&verticesToDraw[0], verticesToDraw.size(), sf::Points);
	}

	
	switch (SimulationSettings::placeObject)
	{
	case 0:
		if (!SimulationSettings::antHillPlaced)
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

void Map::AddPoint(sf::Vector2f position)
{
	verticesToDraw.emplace_back(position);
}

MapPoint* Map::GetPointInsideCircle(sf::Vector2f pos, float radius)
{
	for (auto* point : points)
	{
		if (AntMath::Distance<float>(pos, point->pos) <= radius)
			return point;
	}

	return nullptr;
}

MapPoint* Map::GetFoodInsideCircle(sf::Vector2f pos, float radius)
{
	for (auto* point : points)
	{
		if(point->type == MapPointType::Food)
			if (AntMath::Distance<float>(pos, point->pos) <= radius)
				return point;
	}

	return nullptr;
}

void Map::DrawAntHill()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	this->antHill.setRadius(25.0f);
	this->antHill.setFillColor(this->ConvertColor(SimulationSettings::antHillColor));
	this->antHill.setPosition(sf::Vector2f(mousePosition.x - this->antHill.getRadius(), mousePosition.y - this->antHill.getRadius()));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		SimulationSettings::antHillPlaced = true;

	this->window->draw(this->antHill);
}

void Map::DrawFood()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	sf::CircleShape f;
	f.setRadius(50.0f);
	f.setFillColor(this->ConvertColor(SimulationSettings::foodColor));
	f.setPosition(sf::Vector2f(mousePosition.x - f.getRadius(), mousePosition.y - f.getRadius()));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->food.push_back(f);

	this->window->draw(f);
}

void Map::DrawWalls()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
	this->w.setSize(sf::Vector2f(200.0f, 10.0f));
	this->w.setFillColor(this->ConvertColor(SimulationSettings::wallColor));
	this->w.setPosition(sf::Vector2f(mousePosition.x - this->w.getSize().x / 2, mousePosition.y - this->w.getSize().y / 2));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		this->w.rotate(10.0f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->walls.push_back(this->w);

	this->window->draw(this->w);
}