#pragma once

#include <SFML/Graphics.hpp>

class Application
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	float deltaTime;

public:
	Application();
	~Application();

	void Start();
	void Update();
	void Render();
};