#include "pch.h"
#include "settings.h"

int		SimulationSettings::numberOfAnts = 1;
float	SimulationSettings::antColor[] = { 0.529411f, 0.219078f, 0.011764f, 1 };
float	SimulationSettings::antHillColor[] = { 0.501960f, 0.482352f, 0.478431f , 1 };
bool	SimulationSettings::antHillPlaced = false;
float	SimulationSettings::foodColor[] = { 0.776470f, 0.8f, 0.137254f , 1 };
float	SimulationSettings::wallColor[] = { 1, 1, 1, 1 };
int		SimulationSettings::placeObject = -1;