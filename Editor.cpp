#include "pch.h"
#include "Editor.h"

void Editor::DisplaySettings()
{
	ImGui::Text("Background");
	ImGui::ColorEdit4("Background Color", SimulationSettings::backgroundColor);

	// Ants
	ImGui::Text("Ant Settings");
	ImGui::SliderInt("Number Of Ants", &SimulationSettings::numberOfAnts, 1, 5000);
	ImGui::ColorEdit4("Ant Color 1", SimulationSettings::antColor1);
	ImGui::ColorEdit4("Ant Color 2", SimulationSettings::antColor2);

	// Ant Hill
	ImGui::Text("Ant Hill Settings");
	ImGui::ColorEdit4("Ant Hill Color", SimulationSettings::antHillColor);
	ImGui::RadioButton("Place Ant Hill", &SimulationSettings::placeObject, 0);

	// Food
	ImGui::Text("Food Settings");
	ImGui::ColorEdit4("Food Color", SimulationSettings::foodColor);
	ImGui::RadioButton("Place Food", &SimulationSettings::placeObject, 1);
}

Editor::Editor(sf::RenderWindow* window) : window(window)
{

}

Editor::~Editor()
{
	
}

void Editor::ShowEditor(std::function<void(void)> OnStartSimulation)
{
	ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
	ImGui::Begin("Editor Settings");

	this->DisplaySettings();

	// start Simulation
	if (ImGui::Button("Start", ImVec2(-1.0f, 20.0f)))
		OnStartSimulation();

	// close window
	if (ImGui::Button("Exit", ImVec2(-1.0f, 20.0f)))
		this->window->close();

	ImGui::End();
}