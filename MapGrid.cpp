#include "pch.h"
#include "MapGrid.h"
#include "settings.h"


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
			
			ColorCell(i, sf::Color::Black);

			cells.emplace_back(sf::Vector2f(x, y));

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
	for (auto& cell : cells)
	{
		int idx = GetIndex(cell.position);		

		if(cell.state == AntState::Searching || cell.state == AntState::Returning)
		{
			cell.Update(dt);

			sf::Color c = vertices[idx].color;
			c.a = cell.pheromone[static_cast<uint32_t>(cell.state)] * 255;

			ColorCell(idx, c);
			
		}

		if(cell.type == CellType::Food)
		{
			ColorCell(idx, sf::Color::Green);
		}
		
	}

	//if(SimulationSettings::placeObject == 1)
	{
		if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			auto idx = GetIndex(WorldToMap(ImGui::GetMousePos()));
			cells[idx / 4].type = CellType::Food;
			ColorCell(idx, sf::Color::Yellow);
		}
	}
	
}

void MapGrid::WriteCell(sf::Vector2f position, sf::Vector2f normal, AntState state)
{
	auto* cell = GetCellPtr(position);
	
	if(state == AntState::Searching)
		cell->normal = normal;
		
	cell->pheromone[static_cast<uint32_t>(state)] = 1.f;
	cell->state = state;

	const sf::Color color = state == AntState::Searching ? sf::Color(144, 27, 222) : sf::Color::Red;
	
	ColorCell(GetIndex(cell->position), color);
}

sf::Vector2i MapGrid::WorldToMap(sf::Vector2f position)
{
	return { static_cast<int>(std::floor(position.x / cellSize)), static_cast<int>(std::floor(position.y / cellSize)) };
}

int MapGrid::GetIndex(sf::Vector2i mapPos)
{
	return (mapPos.y * width + mapPos.x) * 4;
}

void MapGrid::ColorCell(int idx, sf::Color color)
{	
	vertices[idx].color = color;
	vertices[idx + 1].color = color;
	vertices[idx + 2].color = color;
	vertices[idx + 3].color = color;
}

GridCell* MapGrid::GetCellPtr(sf::Vector2i index)
{
	const int idx = GetIndex(index) / 4;

	if (idx < 0 || idx >= cells.size())
		return nullptr;

	return &cells[idx];
}

GridCell* MapGrid::GetCellPtr(sf::Vector2f position)
{
	return GetCellPtr(WorldToMap(position));
}

GridCell& MapGrid::GetCell(sf::Vector2i index)
{
	const int idx = GetIndex(index) / 4;

	return cells[idx];
}

GridCell& MapGrid::GetCell(sf::Vector2f position)
{
	return GetCell(WorldToMap(position));
}