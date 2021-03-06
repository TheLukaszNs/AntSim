#include "pch.h"
#include "settings.h"

sf::Vector2u	SimulationSettings::windowSize = sf::Vector2u(0.0, 0.0);
float			SimulationSettings::backgroundColor[] = { 0.f, 0.f, 0.f, 1 };
int				SimulationSettings::numberOfAnts = 1;
float			SimulationSettings::antColor1[] = { 0.123f, 0.868f, 0.233f, 1.000f };
float			SimulationSettings::antColor2[] = { 0.824f, 0.129f, 0.824f, 1.000f };
float			SimulationSettings::antHillColor[] = { 0.501960f, 0.482352f, 0.478431f , 1 };
bool			SimulationSettings::antHillPlaced = false;
sf::Vector2f	SimulationSettings::antHillPosition = sf::Vector2f(960.0f, 540.0f);
float			SimulationSettings::foodColor[] = { 0.776470f, 0.8f, 0.137254f , 1 };
int				SimulationSettings::placeObject = -1;