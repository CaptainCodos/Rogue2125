#pragma once
#include <SFML\Graphics.hpp>

namespace ExtraMaths
{
	float GetRandom(float min, float max);

	/// Pick random number between min[inclusive] and max[exclusive]
	int GetRandomInt(int min, int max);
}