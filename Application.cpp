#include "pch.h"
#include "Application.h"

Application::Application()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Ant Simulations", sf::Style::Fullscreen);
	this->event = sf::Event();

	ImGui::SFML::Init(*window);
}

Application::~Application()
{
	delete this->window;
}

void Application::Start()
{
	while (this->window->isOpen())
	{
		UpdateEvents();
		this->Update();
		this->Render();
	}
}

void Application::UpdateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		ImGui::SFML::ProcessEvent(event);
		
		// close the window
		if (this->event.type == sf::Event::Closed)
		{
			this->window->close();
			ImGui::SFML::Shutdown();
		}
	}
}

void Application::Update()
{
	this->deltaTime = clock.restart();
	
	// Dear ImGui stuff
	ImGui::SFML::Update(*window, deltaTime);
}

void Application::Render()
{
	this->window->clear(sf::Color(176, 119, 79));

	int val{};

	// Dear ImGui stuff
	ImGui::ShowDemoWindow();
	
	ImGui::SFML::Render(*window);

	this->window->display();

}