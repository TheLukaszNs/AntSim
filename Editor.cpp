#include "pch.h"
#include "Editor.h"

void Editor::DisplaySettings()
{
	// Ants
	ImGui::Text("Ant Settings");
	ImGui::SliderInt("Number Of Ants", &SimulationSettings::numberOfAnts, 1, 1000);
	ImGui::ColorEdit4("Ant Color", SimulationSettings::antColor);

	// Ant Hill
	ImGui::Text("Ant Hill Settings");
	ImGui::ColorEdit4("Ant Hill Color", SimulationSettings::antHillColor);
	ImGui::RadioButton("Place Ant Hill", &SimulationSettings::placeObject, 0);

	// Food
	ImGui::Text("Food Settings");
	ImGui::ColorEdit4("Food Color", SimulationSettings::foodColor);
	ImGui::RadioButton("Place Food", &SimulationSettings::placeObject, 1);

	// Walls
	ImGui::Text("Wall Settings");
	ImGui::ColorEdit4("Wall Color", SimulationSettings::wallColor);
	ImGui::RadioButton("Place Wall", &SimulationSettings::placeObject, 2);
}

Editor::Editor(sf::RenderWindow* window) : window(window)
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