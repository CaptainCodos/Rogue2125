#pragma once

#include <SFML\Graphics.hpp>

namespace DataShapes
{
	struct Circle
	{
		float radius;
		sf::Vector2f pos;

		Circle();
		Circle(float rad, sf::Vector2f p);

		bool Intersects(Circle other);		// Check for intersection
		bool Intersects(Circle other, float &depth);	// Check for intersection and return penetration depth (A to B)
		bool Intersects(Circle other, sf::Vector2f &depth);		// Check for intersection and return depth vector (A to B)
	};

	struct Rectangle
	{
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::Vector2f centre;

		Rectangle();
		Rectangle(sf::Vector2f p, sf::Vector2f s);

		sf::Vector2f GetPosCentre();
		void SetSize(sf::Vector2f s);
		void SetPosCentre(sf::Vector2f p);

		bool Intersects(Rectangle other);	// Check for intersection
		bool Intersects(Rectangle other, float &depth, int &dir);	// Check for intersection and return penetration depth and direction (A to B)
		bool Intersects(Rectangle other, sf::Vector2f &depth, int &dir);	// Check for intersection and return depth vector and direction (A to B)
	};
}
