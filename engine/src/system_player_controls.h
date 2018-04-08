#pragma once

#include <SFML/Window/Keyboard.hpp>
//#include "remap_controls.h"

using namespace sf;

namespace Input
{
	bool GetKeyDown(Keyboard::Key key);		// Simple key press trigger
	bool GetKeyPressed(Keyboard::Key key);	// For single frame
	bool GetKeyHeld(Keyboard::Key key);		// Get key held down

	bool GetMouseDown(Mouse::Button button);	// Simple mouse click trigger
	bool GetMousePressed(Mouse::Button button);	// For single frame

	float GetAxisValue(int axis);	// Returns direction value from axis, 0 = horizontal, 1 = vertical
};

namespace controls 
{
	void CheckCameraInput(View &view, float &zoom, double dt) 
	{
		// THIS DOES NOT WORK

		/*if (Keyboard::isKeyPressed(PlayerControls::GetKey("Up")))
		{
			view.move(0, -dt * 300.0f);
		}
		if (Keyboard::isKeyPressed(PlayerControls::GetKey("Left")))
		{
			view.move(-dt * 300.0f, 0);
		}
		if (Keyboard::isKeyPressed(PlayerControls::GetKey("Down")))
		{
			view.move(0, dt * 300.0f);
		}
		if (Keyboard::isKeyPressed(PlayerControls::GetKey("Right")))
		{
			view.move(dt * 300.0f, 0);
		}*/

		// THIS DOES

		if (Keyboard::isKeyPressed(Keyboard::W)) 
		{
			view.move(0, -dt * 300.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) 
		{
			view.move(-dt * 300.0f, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) 
		{
			view.move(0, dt * 300.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) 
		{
			view.move(dt * 300.0f, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) 
		{
			zoom += dt;
		}
		if (Keyboard::isKeyPressed(Keyboard::E)) 
		{
			zoom -= dt;
		}

		view.zoom(zoom);

		zoom = 1.0f;
		Engine::GetWindow().setView(view);
	}
}