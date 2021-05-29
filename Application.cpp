#include "pch.h"
#include "Application.h"

Application::Application()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Ant Simulations", sf::Style::Fullscreen);
	this->event = sf::Event();
	this->editor = new Editor(this->window);
	this->editorVisible = false;

	ImGui::SFML::Init(*window);
}

Application::~Application()
{
	delete this->window;
	delete this->editor;
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
	
	// Dear ImGui stuff
	ImGui::SFML::Update(*window, deltaTime);
}

void Application::Render()
{
	this->window->clear(sf::Color(176, 119, 79));

	// Dear ImGui stuff
	ImGui::ShowDemoWindow();
	// show Editor
	if (this->editorVisible)
		this->editor->ShowEditor();

	ImGui::SFML::Render(*window);

	this->window->display();

}