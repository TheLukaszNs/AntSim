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
	//this->windowSettings = ImGui::GetIO();
	//this->windowSettings.WantCaptureMouse = false;
}

void Map::Render()
{
	this->window->clear(this->ConvertColor(this->settings->backgroundColor));

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
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->antHill.setRadius(25.0f);
	this->antHill.setFillColor(this->ConvertColor(this->settings->antHillColor));
	this->antHill.setOrigin(sf::Vector2f(this->antHill.getRadius(), this->antHill.getRadius()));
	this->antHill.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->food.size() == 0)
			this->settings->antHillPlaced = true;

		else
		{
			int size = this->food.size();
			bool canBePlaced = true;

			for (int i = 0; i < size; i++)
				if (this->antHill.getRadius() + this->food[i].getRadius() > AntMath::Magnitude<float>(this->antHill.getPosition() - this->food[i].getPosition()))
				{
					canBePlaced = false;
					break;
				}

			if (canBePlaced)
				this->settings->antHillPlaced = true;
		}
	}

	this->window->draw(this->antHill);
}

void Map::DrawFood()
{
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	sf::CircleShape f;
	f.setRadius(50.0f);
	f.setFillColor(this->ConvertColor(this->settings->foodColor));
	f.setOrigin(sf::Vector2f(f.getRadius(), f.getRadius()));
	f.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		// nie ma mrowiska i jedzenia
		if (this->settings->antHillPlaced == false && this->food.size() == 0)
			this->food.push_back(f);

		// nie ma mrowiska, jest jedzenie
		else if (this->settings->antHillPlaced == false && this->food.size() > 0)
		{
			bool canBePlaced = true;
			int size = this->food.size();

			for (int i = 0; i < size; i++)
				if (2 * f.getRadius() > AntMath::Magnitude<float>(this->food[i].getPosition() - mousePosition))
				{
					canBePlaced = false;
					break;
				}

			if (canBePlaced)
				this->food.push_back(f);
		}

		// jest mrowisko, nie ma jedzenia
		else if (this->settings->antHillPlaced && this->food.size() == 0)
		{
			if (this->antHill.getRadius() + f.getRadius() <= AntMath::Magnitude<float>(this->antHill.getPosition() - mousePosition))
				this->food.push_back(f);
		}

		// to i to jest
		else
		{
			bool canBePlaced = true;
			int size = this->food.size();

			for (int i = 0; i < size; i++)
			{
				if (2 * f.getRadius() > AntMath::Magnitude<float>(this->food[i].getPosition() - mousePosition) ||
					this->antHill.getRadius() + f.getRadius() > AntMath::Magnitude<float>(this->antHill.getPosition() - mousePosition))
				{
					canBePlaced = false;
					break;
				}
			}

			if (canBePlaced)
				this->food.push_back(f);
		}
	}

	this->window->draw(f);
}

void Map::DrawWalls()
{
	sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->w.setSize(sf::Vector2f(200.0f, 10.0f));
	this->w.setFillColor(this->ConvertColor(this->settings->wallColor));
	this->w.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
	this->w.setOrigin(sf::Vector2f(this->w.getSize().x / 2, this->w.getSize().y / 2));

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		this->w.rotate(45.0f);

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		this->walls.push_back(this->w);

	this->window->draw(this->w);
}
