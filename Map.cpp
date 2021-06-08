#include "pch.h"
#include "Map.h"

sf::Color Map::ConvertColor(float color[4])
{
	return sf::Color(static_cast<sf::Uint32>(color[0] * 255), static_cast<sf::Uint32>(color[1] * 255), static_cast<sf::Uint32>(color[2] * 255), 255);
}

void Map::DisplayAll()
{
	this->window->draw(this->antHill);
}

Map::Map(sf::RenderWindow* window) : window(window)
{
	grid = new MapGrid(window->getSize().x, window->getSize().y, 2);
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
		//window->draw(&verticesToDraw[0], verticesToDraw.size(), sf::Points);
	}

	switch (SimulationSettings::placeObject)
	{
	case 0:
		if (!SimulationSettings::antHillPlaced)
			this->DrawAntHill();
		break;

	default:
		break;
	}

	this->DisplayAll();
}

void Map::AddPoint(sf::Vector2f position, AntState state, sf::Vector2f prevPos = sf::Vector2f(0, 0))
{
	//verticesToDraw.emplace_back(position);

	grid->WriteCell(position, AntMath::NormalizeVector(prevPos - position), state);
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
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->antHill.setRadius(25.0f);
	this->antHill.setFillColor(this->ConvertColor(SimulationSettings::antHillColor));
	this->antHill.setOrigin(sf::Vector2f(this->antHill.getRadius(), this->antHill.getRadius()));
	this->antHill.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
	SimulationSettings::antHillPosition = this->antHill.getPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		SimulationSettings::antHillPlaced = true;

	}

	this->window->draw(this->antHill);
}
