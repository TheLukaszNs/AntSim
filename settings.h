#pragma once

struct SimulationSettings
{
	// Editor 
	float backgroundColor[4] = { 0.690196, 0.466666, 0.309803, 1 };

	// Ants
	static int numberOfAnts;
	static float antColor[4];

	// Ant Hill
	static float antHillColor[4];
	static bool antHillPlaced;

	// Food
	static float foodColor[4];

	// Walls
	static float wallColor[4];

	// Switch
	static int placeObject;
};

