#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

using namespace std;
using namespace sf;

namespace Input
{
	bool GetKeyDown(Keyboard::Key key);

	// For single frame
	bool GetKeyPressed(Keyboard::Key key);

	// Get key held down
	bool GetKeyHeld(Keyboard::Key key);

	// Simple mouse click trigger
	bool GetMouseDown(Mouse::Button button);

	// For single frame
	bool GetMousePressed(Mouse::Button button);

	// Returns direction value from axis, 0 = horizontal, 1 = verticals
	float GetAxisValue(int axis);

	bool MouseInWindow();
	Vector2i GetMouseWindowPos();
	Vector2i GetMouseRelativeToPos(Vector2i pos);
};

namespace controls 
{
	void CheckCameraInput(View &view, float &zoom, double dt);

	void GetMouseClick();

	void GetMousePos();
}