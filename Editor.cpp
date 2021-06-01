#include "pch.h"
#include "Editor.h"

void Editor::DisplaySettings()
{
	// Ants
	ImGui::Text("Ant Settings");
	ImGui::SliderInt("Number Of Ants", &this->settings->numberOfAnts, 1, 1000);
	ImGui::ColorEdit4("Ant Color", this->settings->antColor);

	// Ant Hill
	ImGui::Text("Ant Hill Settings");
	ImGui::ColorEdit4("Ant Hill Color", this->settings->antHillColor);
	ImGui::RadioButton("Place Ant Hill", &this->settings->placeObject, 0);

	// Food
	ImGui::Text("Food Settings");
	ImGui::ColorEdit4("Food Color", this->settings->foodColor);
	ImGui::RadioButton("Place Food", &this->settings->placeObject, 1);

	// Walls
	ImGui::Text("Wall Settings");
	ImGui::ColorEdit4("Wall Color", this->settings->wallColor);
	ImGui::RadioButton("Place Wall", &this->settings->placeObject, 2);
}

Editor::Editor(sf::RenderWindow* window, SimulationSettings* settings) : window(window), settings(settings)
{

}

Editor::~Editor()
{
	
}

void Editor::ShowEditor()
{
	ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
	ImGui::Begin("Editor Settings");

	this->DisplaySettings();

	// close window
	if (ImGui::Button("Exit", ImVec2(-1.0f, 20.0f)))
		this->window->close();

	ImGui::End();
}