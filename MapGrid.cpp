#include "pch.h"
#include "MapGrid.h"

MapGrid::MapGrid()
{
}

MapGrid::MapGrid(float width_, float height_, int cellSize_) : width(std::ceil(width_ / cellSize_)), height(std::ceil(height_ / cellSize_)), cellSize(cellSize_)
{
	vertices.resize(width * height * 4);

	int i = 0;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			vertices[i].position		= sf::Vector2f((x * cellSize), (y * cellSize));
			vertices[i + 1].position	= sf::Vector2f((x * cellSize) + cellSize, (y * cellSize));
			vertices[i + 2].position	= sf::Vector2f((x * cellSize) + cellSize, (y * cellSize) + cellSize);
			vertices[i + 3].position	= sf::Vector2f((x * cellSize), (y * cellSize) + cellSize);

			uint8_t val = AntMath::Random::get<uint8_t>(0, 255);
			vertices[i].color = sf::Color::Black;
			vertices[i + 1].color = sf::Color::Black;
			vertices[i + 2].color = sf::Color::Black;
			vertices[i + 3].color = sf::Color::Black;

			cells.push_back(GridCell());

			i += 4;

		}
	}
}

MapGrid::~MapGrid()
{
}

void MapGrid::Render(sf::RenderWindow* window)
{
	window->draw(&vertices[0], vertices.size(), sf::Quads);
}

void MapGrid::Update(const float& dt)
{
	sf::Vector2f worldpos = ImGui::GetMousePos();

	auto mapPos = WorldToMap(worldpos);
	int idx = GetIndex(mapPos);

	if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && idx >= 0)
	{
		vertices[idx].color = sf::Color(144, 27, 222);
		vertices[idx + 1].color = sf::Color(144, 27, 222);
		vertices[idx + 2].color = sf::Color(144, 27, 222);
		vertices[idx + 3].color = sf::Color(144, 27, 222);
	}
	
}

sf::Vector2i MapGrid::WorldToMap(sf::Vector2f position)
{
	return { static_cast<int>(std::floor(position.x / cellSize)), static_cast<int>(std::floor(position.y / cellSize)) };
}

int MapGrid::GetIndex(sf::Vector2i mapPos)
{
	return (mapPos.y * width + mapPos.x) * 4;
}