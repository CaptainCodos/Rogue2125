#include "data_shapes.h"
#include "maths.h"

using namespace sf;

using namespace DataShapes;

#pragma region Circle

Circle::Circle()
{
	radius = 1.0f;
	pos = Vector2f(0.0f, 0.0f);
}

Circle::Circle(float rad, sf::Vector2f p)
{
	radius = rad;
	pos = p;
}

bool Circle::Intersects(Circle other)
{
	Vector2f r = other.pos - pos;

	return (radius + other.radius > length(r));
}

bool Circle::Intersects(Circle other, float &depth)
{
	Vector2f r = other.pos - pos;

	depth = 0.0f;

	if (radius + other.radius > length(r))
	{
		depth = radius + other.radius - length(r);
		return true;
	}

	return false;
}

bool Circle::Intersects(Circle other, Vector2f &depth)
{
	Vector2f r = other.pos - pos;

	depth = Vector2f(0.0f, 0.0f);

	if (radius + other.radius > length(r))
	{
		float d = radius + other.radius - length(r);
		depth = normalize(r) * d;

		return true;
	}

	return false;
}

#pragma endregion

#pragma region Rectangle

Rectangle::Rectangle()
{
	pos = Vector2f(0.0f, 0.0f);
	size = Vector2f(1.0f, 1.0f);
	centre = size / 2.0f;
}

Rectangle::Rectangle(Vector2f p, Vector2f s)
{
	pos = p;
	size = s;
	centre = s / 2.0f;
}

Vector2f Rectangle::GetPosCentre() { return pos + centre; }
void Rectangle::SetSize(Vector2f s) { size = s; centre = s / 2.0f; }
void Rectangle::SetPosCentre(Vector2f p) { centre = p; pos = p - centre; }

bool Rectangle::Intersects(Rectangle other)
{
	Vector2f r = other.pos - pos;

	bool x = other.centre.x + centre.x > abs(r.x);
	bool y = other.centre.y + centre.y > abs(r.y);

	return x && y;
}

bool Rectangle::Intersects(Rectangle other, float &depth, int &dir)
{
	Vector2f r = other.pos - pos;

	bool x = other.centre.x + centre.x > abs(r.x);
	bool y = other.centre.y + centre.y > abs(r.y);

	depth = 0.0f;
	dir = 0;

	if (x && y)
	{
		float ratio = abs(r.x) / abs(r.y);

		if (ratio > 1.0f)
		{
			depth = r.x;
		}
		else
		{
			dir = 1;
			depth = r.y;
		}

		return true;
	}

	return false;
}

bool Rectangle::Intersects(Rectangle other, sf::Vector2f &depth, int &dir)
{
	Vector2f r = other.pos - pos;

	bool x = other.centre.x + centre.x > abs(r.x);
	bool y = other.centre.y + centre.y > abs(r.y);

	depth = Vector2f(0.0f, 0.0f);
	dir = 0;

	if (x && y)
	{
		float ratio = abs(r.x) / abs(r.y);

		if (ratio > 1.0f)
		{
			depth = r;
		}
		else
		{
			dir = 1;
			depth = r;
		}

		return true;
	}

	return false;
}

#pragma endregion
