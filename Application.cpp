#include "Application.h"

Application::Application()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Ant Simulations", sf::Style::Fullscreen);
	this->event = sf::Event();
}

Application::~Application()
{
	delete this->window;
}

void Application::Start()
{
	while (this->window->isOpen())
	{
		this->Update();
		this->Render();
	}
}

void Application::Update()
{
	this->deltaTime = clock.restart().asSeconds();

	while (this->window->pollEvent(this->event))
	{
		// close the window
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Application::Render()
{
	this->window->clear(sf::Color::Black);
	this->window->display();
}