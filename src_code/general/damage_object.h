#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct DmgData
{
	int actorID;

	sf::Vector2f vel;
	float angle;

	float dmg;
	std::vector<int> types;
	std::string actor;
};