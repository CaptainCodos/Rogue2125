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
void Rectangle::SetPosCentre(Vector2f p) { pos = p - centre; }

float Rectangle::GetTop() { return pos.y; }
float Rectangle::GetBottom() { return pos.y + size.y; }
float Rectangle::GetLeft() { return pos.x; }
float Rectangle::GetRight() { return pos.x + size.x; }

Vector2f Rectangle::GetTL() { return Vector2f(pos.x, pos.y); }
Vector2f Rectangle::GetTR() { return Vector2f(pos.x + size.x, pos.y); }
Vector2f Rectangle::GetBL() { return Vector2f(pos.x, pos.y + size.y); }
Vector2f Rectangle::GetBR() { return Vector2f(pos.x + size.x, pos.y + size.y); }

bool Rectangle::Intersects(Rectangle other)
{
	Vector2f r = other.GetPosCentre() - GetPosCentre();

	bool x = abs(r.x) * 2 < (size.x + other.size.x);
	bool y = abs(r.y) * 2 < (size.y + other.size.y);

	return x && y;
}

bool Rectangle::Intersects(Rectangle other, float &depth, sf::Vector2i &axis)
{
	Vector2f r = other.GetPosCentre() - GetPosCentre();

	bool x = abs(r.x) * 2 < (size.x + other.size.x);
	bool y = abs(r.y) * 2 < (size.y + other.size.y);

	depth = 0.0f;
	axis = Vector2i(0, 0);

	if (x && y)
	{
		float ratio = 0.0f;

		if (r.y != 0.0f)
			ratio = r.x / r.y;

		if (ratio > 1.0f || ratio < -1.0f)
		{
			if (r.x < 0.0f)
				axis.x = -1;
			else
				axis.x = 1;

			depth = r.x;
		}
		else
		{
			if (r.y < 0.0f)
				axis.y = -1;
			else
				axis.y = 1;

			depth = r.y;
		}

		return true;
	}

	return false;
}

bool Rectangle::Intersects(Rectangle other, sf::Vector2f &depth, sf::Vector2i &axis)
{
	Vector2f r = other.GetPosCentre() - GetPosCentre();

	bool x = abs(r.x) * 2 < (size.x + other.size.x);
	bool y = abs(r.y) * 2 < (size.y + other.size.y);

	depth = Vector2f(0.0f, 0.0f);
	axis = Vector2i(0, 0);

	if (x && y)
	{
		float ratio = 0.0f;

		if (r.y != 0.0f)
			ratio = r.x / r.y;

		if (ratio > 1.0f || ratio < -1.0f)
		{
			if (r.x < 0.0f)
				axis.x = -1;
			else
				axis.x = 1;

			depth.x = r.x;
		}
		else
		{
			if (r.y < 0.0f)
				axis.y = -1;
			else
				axis.y = 1;

			depth.y = r.y;
		}

		return true;
	}

	return false;
}

bool Rectangle::Contains(Vector2f p)
{
	return (pos.x < p.x && p.x < pos.x + size.x) && (pos.y < p.y && p.y < pos.y + size.y);
}

bool Rectangle::Contains(Vector2f p, float &depth, Vector2i &axis)
{
	bool contained = (pos.x < p.x && p.x < pos.x + size.x) && (pos.y < p.y && p.y < pos.y + size.y);

	depth = 0.0f;
	axis = Vector2i(0, 0);

	if (contained)
	{
		Vector2f r = p - (pos + centre);

		float ratio = 0.0f;

		if (r.y != 0.0f)
			ratio = r.x / r.y;

		if (ratio > 1.0f || ratio < -1.0f)
		{
			if (r.x < 0.0f)
				axis.x = -1;
			else
				axis.x = 1;

			depth = r.x;
		}
		else
		{
			if (r.y < 0.0f)
				axis.y = -1;
			else
				axis.y = 1;

			depth = r.y;
		}

		return true;
	}

	return false;
}

#pragma endregion
