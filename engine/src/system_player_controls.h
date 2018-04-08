#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "remap_controls.h"
#include <iostream>

using namespace std;
using namespace sf;

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

	void GetMouseClick() {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			cout << "\r" << "Left Click Pressed." << endl;
		}
	}

	void GetMousePos() {
		cout << "\r" << Mouse::getPosition() << std::flush;
	}
}