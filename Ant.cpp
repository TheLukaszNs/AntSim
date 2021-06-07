#include "pch.h"
#include "Ant.h"

#include "Map.h"

Ant::Ant(Map* map) : map(map)
{
	shape.setFillColor(sf::Color::White);
	shape.setRadius(5.f);
	position = SimulationSettings::antHillPosition;
	shape.setPosition(position);
}

Ant::~Ant()
{
}

void Ant::Wander(const float& dt)
{
	prevPos = position;
	
	direction = AntMath::NormalizeVector(direction + AntMath::RandomInUnitCircle() * (state == AntState::Searching ? 0.05f : 0.f));

	sf::Vector2f desVel = direction * speed;
	sf::Vector2f desSteeringForce = (desVel - velocity) * speed;
	sf::Vector2f acceleration = AntMath::ClampMagnitude(desSteeringForce, speed) / 1.f;
	
	velocity = AntMath::ClampMagnitude(velocity + acceleration * dt, speed);
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
		shape.setFillColor(sf::Color::Blue);
	}

	if(state == AntState::Returning)
	{
		//direction = map->grid->GetCell(position).normal;
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
	
	float bestFit = 0.f;
	sf::Vector2f bestDir;
	GridCell* bestCell = nullptr;
	int samples = 32;

	const auto numState = state == AntState::Searching ? 1 : 0;
	
	while(samples --> 0)
	{
		const float sampleAngle = currAngle + AntMath::Random::get(0.f, sampleAngleRange);
		const float distance = AntMath::Random::get(0.f, 50.f);
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

		//printf("Found best move! pheromone: %f\n", bestFit);

		
		direction = AntMath::NormalizeVector(bestDir);
	}
}

void Ant::Update(const float& dt)
{

	Wander(dt);
	HandleFood();

	
	accumulatedTime += dt;
	if (accumulatedTime > .01f)
	{
		map->AddPoint(position, state, prevPos);
		GetBestMove();


		accumulatedTime = 0.f;
	}




	
	if(state == AntState::Returning)
	{

		if(AntMath::Distance(position, SimulationSettings::antHillPosition) <= 50.f)
		{
			state = AntState::Searching;
			shape.setFillColor(sf::Color::White);
		}
	}
	else
	{

	}
	

	
	shape.setPosition(position);
}

void Ant::Render(sf::RenderWindow* window)
{
	//window->draw(shape);
}
