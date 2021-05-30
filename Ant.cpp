#include "pch.h"
#include "Ant.h"

Ant::Ant()
{
	shape.setFillColor(sf::Color::Black);
	shape.setRadius(8.f);
	position = { 1000.f, 600.f };
	shape.setPosition(position);
}

Ant::~Ant()
{
}

void Ant::Update(const float& dt)
{
	direction = AntMath::NormalizeVector(direction + AntMath::RandomInUnitCircle() * 0.1f);

	sf::Vector2f desVel = direction * 100.f;
	sf::Vector2f desSteeringForce = (desVel - velocity) * 100.f;
	sf::Vector2f acceleration = AntMath::ClampMagnitude(desSteeringForce, 100.f) / 1.f;
	
	velocity = AntMath::ClampMagnitude(velocity + acceleration * dt, 100.f);
	position += velocity * dt;

	shape.setPosition(position);
}

void Ant::Render(sf::RenderWindow* window)
{
	window->draw(shape);
}
