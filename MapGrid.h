#pragma once

#include "AntState.h"


enum class CellType
{
	Neutral, Food
};

struct GridCell
{
	sf::Vector2i position;
	
	AntState state;
	
	CellType type = CellType::Neutral;

	float pheromone[2] = { 0.f, 0.f };

	GridCell(sf::Vector2f pos) : position(pos)
	{

	}

	void Update(const float& dt)
	{
		pheromone[0] -= 0.08f * dt;
		pheromone[1] -= 0.08f * dt;
		
		pheromone[0] = std::max(pheromone[0], 0.f);
		pheromone[1] = std::max(pheromone[1], 0.f);
	}
};

class MapGrid
{
private:
	int width, height;
	int cellSize;

	std::vector<sf::Vertex> vertices;
	std::vector<GridCell> cells;

public:
	MapGrid();
	MapGrid(float width_, float height_, int cellSize_);
	~MapGrid();

	void Render(sf::RenderWindow* window);
	void Update(const float& dt);

	void WriteCell(sf::Vector2f position, AntState state);
	sf::Vector2i WorldToMap(sf::Vector2f);
	int GetIndex(sf::Vector2i);
	void ColorCell(int idx, sf::Color color);
	GridCell* GetCellPtr(sf::Vector2i);
	GridCell* GetCellPtr(sf::Vector2f);
	GridCell& GetCell(sf::Vector2i);
	GridCell& GetCell(sf::Vector2f);
};

