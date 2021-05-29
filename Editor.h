#pragma once

class Editor
{
private:
	sf::RenderWindow* window;

public:
	Editor(sf::RenderWindow* window);
	~Editor();

	void ShowEditor();
};