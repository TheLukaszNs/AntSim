#pragma once

#include <imgui.h>
#include <imgui-SFML.h>

class Application
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Time deltaTime;
	bool editorVisible;

	void ShowEditor();

public:
	Application();
	~Application();

	void Start();
	void UpdateEvents();
	void Update();
	void Render();
};