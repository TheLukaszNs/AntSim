#pragma once

struct SimulationSettings
{
	// Editor 
	float backgroundColor[4] = { 0.690196, 0.466666, 0.309803, 1 };

	// Ants
	int numberOfAnts = 1;
	float antColor[4] = { 0.529411, 0.219078, 0.011764, 1 };

	// Ant Hill
	float antHillColor[4] = { 0.501960, 0.482352, 0.478431 , 1 };
	bool antHillPlaced = false;

	// Food
	float foodColor[4] = { 0.776470, 0.8, 0.137254 , 1 };

	// Walls
	float wallColor[4] = { 1, 1, 1, 1 };

	// Switch
	int placeObject;
};