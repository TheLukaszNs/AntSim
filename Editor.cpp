#include "pch.h"
#include "Editor.h"

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
	// ...
	// close window
	if (ImGui::Button("Exit", ImVec2(-1.0f, 20.0f)))
		this->window->close();

	ImGui::End();
}