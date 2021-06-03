#pragma once

struct GridCell
{
	int t = 0;
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

	sf::Vector2i WorldToMap(sf::Vector2f);
	int GetIndex(sf::Vector2i);
};

