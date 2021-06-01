#pragma once

struct SimulationSettings
{
	// Ants
	int numberOfAnts;
	float antColor[4] = { 0.529411, 0.219078, 0.011764, 1 };

	// Ant Hill
	float antHillColor[4] = { 0.501960, 0.482352, 0.478431 , 1 };
	bool antHillPlaced = false;

	// Food
	float foodColor[4] = { 0.776470, 0.8, 0.137254 , 1 };

	// Walls
	float wallColor[4] = { 1, 1, 1, 1 };

	int placeObject;
};