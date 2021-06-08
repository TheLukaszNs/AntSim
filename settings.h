#pragma once

struct SimulationSettings
{
	static sf::Vector2u windowSize;

	// Editor 
	static float backgroundColor[4];

	// Ants
	static int numberOfAnts;
	static float antColor1[4];
	static float antColor2[4];

	// Ant Hill
	static float antHillColor[4];
	static bool antHillPlaced;
	static sf::Vector2f antHillPosition;

	// Food
	static float foodColor[4];

	// Switch
	static int placeObject;
};

