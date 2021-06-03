#pragma once

struct SimulationSettings
{
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

	static int placeObject;
};

