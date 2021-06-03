#include "pch.h"
#include "Ant.h"

Ant::Ant(Map* map) : map(map)
{
	shape.setFillColor(sf::Color::White);
	shape.setRadius(2.f);
	position = { 960.f, 560.f };
	shape.setPosition(position);
}

Ant::~Ant()
{
}

void Ant::Wander(const float& dt)
{
	direction = AntMath::NormalizeVector(direction + AntMath::RandomInUnitCircle() * 0.05f);

	sf::Vector2f desVel = direction * 50.f;
	sf::Vector2f desSteeringForce = (desVel - velocity) * 50.f;
	sf::Vector2f acceleration = AntMath::ClampMagnitude(desSteeringForce, 50.f) / 1.f;
	
	velocity = AntMath::ClampMagnitude(velocity + acceleration * dt, 50.f);
	position += velocity * dt;
}

void Ant::HandleFood()
{
	if(state == AntState::Searching)
	{
		auto* p = map->GetFoodInsideCircle(position, 20.f);
		if(p)
		{
			//printf("%f\n", p->pos.x);
		}
	}
}

void Ant::Update(const float& dt)
{
	Wander(dt);
	HandleFood();

	accumulatedTime += dt;

	if (accumulatedTime > .15f)
	{
		map->AddPoint(position);
		
		accumulatedTime = 0.f;
	}
	
	shape.setPosition(position);
}

void Ant::Render(sf::RenderWindow* window)
{
	window->draw(shape);
}
