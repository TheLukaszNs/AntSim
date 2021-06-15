#include "pch.h"
#include "Ant.h"
#include "Map.h"

Ant::Ant(Map* map) : map(map)
{
	shape.setFillColor(AntMath::ConvertColor(SimulationSettings::antColor1));
	shape.setRadius(5.f);
	position = SimulationSettings::antHillPosition;
	shape.setPosition(position);
}

Ant::~Ant()
{

}

void Ant::Wander(const float& dt)
{
	if(state == AntState::Searching)
	{
		direction = AntMath::NormalizeVector(direction + AntMath::RandomInUnitCircle() * 0.05f);

		sf::Vector2f desVel = direction * speed;
		sf::Vector2f desSteeringForce = (desVel - velocity) * speed;
		sf::Vector2f acceleration = AntMath::ClampMagnitude(desSteeringForce, speed) / 1.f;
		velocity = AntMath::ClampMagnitude(velocity + acceleration * dt, speed);
	}

	else
		velocity = direction * speed;
	
	position += velocity * dt;

	if (position.x <= 0.f || position.x >= 1920.f || position.y <= 0.f || position.y >= 1080.f) position = SimulationSettings::antHillPosition;
}

void Ant::HandleFood()
{
	if (state == AntState::Searching && map->grid->GetCell(position).type == CellType::Food)
	{
		state = AntState::Returning;
		direction *= -1.f;
		velocity *= -1.f;
		shape.setFillColor(AntMath::ConvertColor(SimulationSettings::antColor2));
	}
}

bool Ant::CheckBoundaries()
{
	return true;
}

void Ant::GetBestMove()
{
	const float sampleAngleRange = 0.8f * AntMath::PI;
	const float currAngle = AntMath::Angle(direction);
	
	float bestFit = 0.0f;
	sf::Vector2f bestDir;
	GridCell* bestCell = nullptr;
	int samples = 32;

	const auto numState = state == AntState::Searching ? 1 : 0;
	
	while(samples --> 0)
	{
		const float sampleAngle = currAngle + AntMath::Random::get(-sampleAngleRange / 2, sampleAngleRange / 2);
		const float distance = AntMath::Random::get(30.f, 50.f);
		const sf::Vector2f dirToCell = { cos(sampleAngle), sin(sampleAngle) };
		auto* cell = map->grid->GetCellPtr(position + distance * dirToCell);

		if (!cell) continue;
		
		if(cell->pheromone[numState] > bestFit)
		{
			bestFit = cell->pheromone[numState];
			bestDir = dirToCell;
			bestCell = cell;
		}
	}

	if(bestFit > 0.f)
	{
		bestCell->pheromone[!numState] *= 0.99f;
		direction = bestDir;
	}
}

void Ant::Update(const float& dt)
{
	GetBestMove();
	Wander(dt);
	HandleFood();

	map->AddPoint(position, state);
	accumulatedTime += dt;

	if (accumulatedTime > .001f)
		accumulatedTime = 0.f;
	
	if(state == AntState::Returning)
		if(AntMath::Distance(position, SimulationSettings::antHillPosition) <= 25.0f)
		{
			state = AntState::Searching;
			shape.setFillColor(AntMath::ConvertColor(SimulationSettings::antColor2));
		}

	shape.setPosition(position);
}

void Ant::Render(sf::RenderWindow* window)
{
	//window->draw(shape);
}
