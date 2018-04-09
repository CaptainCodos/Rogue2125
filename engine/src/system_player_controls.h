#pragma once

#include <SFML/Window/Keyboard.hpp>
//#include "remap_controls.h"

using namespace sf;

namespace Input
{
	// Simple key press trigger
	bool GetKeyDown(Keyboard::Key key) {
		Engine::GetWindow().setKeyRepeatEnabled(true);
		if (Keyboard::isKeyPressed(key)) {		
			return true;
		}
	}
	// For single frame
	bool GetKeyPressed(Keyboard::Key key) {
		Engine::GetWindow().setKeyRepeatEnabled(false);
		if (Keyboard::isKeyPressed(key)) {
			return true;
		}
	}
	// Get key held down
	bool GetKeyHeld(Keyboard::Key key) {
		Engine::GetWindow().setKeyRepeatEnabled(true);
		if (Keyboard::isKeyPressed(key)) {
			return true;
		}
	}
	//// Simple mouse click trigger
	//bool GetMouseDown(Mouse::Button button) {

	//}
	//// For single frame
	//bool GetMousePressed(Mouse::Button button) {

	//}
	//// Returns direction value from axis, 0 = horizontal, 1 = verticals
	//float GetAxisValue(int axis) {

	//}
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