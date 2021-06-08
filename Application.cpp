#include "pch.h"
#include "Application.h"

Application::Application()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Ant Simulations", sf::Style::Fullscreen);
	SimulationSettings::windowSize = this->window->getSize();
	this->event = sf::Event();
	this->editor = new Editor(this->window);
	this->editorVisible = true;
	this->map = new Map(this->window);

	window->setKeyRepeatEnabled(false);
	

	ImGui::SFML::Init(*window);
}

Application::~Application()
{
	delete this->window;
	delete this->editor;

	for (auto* ant : ants)
	{
		delete ant;
	}

	delete map;
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

		// any key pressed
		if (this->event.type == sf::Event::KeyPressed)
		{
			// show / close Editor
			if (this->event.key.code == sf::Keyboard::E)
				this->editorVisible = this->editorVisible ? false : true;
		}
	}
}

void Application::Update()
{
	this->deltaTime = clock.restart();

	this->map->Update(deltaTime.asSeconds());
	
	for (const auto& ant : ants)
	{
		ant->Update(deltaTime.asSeconds());
	}
	
	// Dear ImGui stuff
	ImGui::SFML::Update(*window, deltaTime);
}

void Application::Render()
{
	this->window->clear(AntMath::ConvertColor(SimulationSettings::backgroundColor));

	this->map->Render();

	// Dear ImGui stuff
	ImGui::ShowDemoWindow();
	// show Editor
	if (this->editorVisible)
		this->editor->ShowEditor([&]() {
		for (int i = 0; i < SimulationSettings::numberOfAnts; i++)
			ants.push_back(new Ant(map));
			});

	for (auto* ant : ants)
	{
		ant->Render(window);
	}

	ImGui::SFML::Render(*window);

	this->window->display();

}