#include "pch.h"
#include "Map.h"

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

	// place Ant Hill
	if (SimulationSettings::placeObject == 0)
		if (!SimulationSettings::antHillPlaced)
			this->DrawAntHill();

	this->DisplayAll();
}

void Map::AddPoint(sf::Vector2f position, AntState state)
{
	grid->WriteCell(position, state);
}

void Map::DrawAntHill()
{
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->antHill.setRadius(25.0f);
	this->antHill.setFillColor(AntMath::ConvertColor(SimulationSettings::antHillColor));
	this->antHill.setOrigin(sf::Vector2f(this->antHill.getRadius(), this->antHill.getRadius()));
	this->antHill.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
	SimulationSettings::antHillPosition = this->antHill.getPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		SimulationSettings::antHillPlaced = true;

	this->window->draw(this->antHill);
}
