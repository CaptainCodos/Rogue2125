#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

using namespace std;
using namespace sf;

namespace input
{
	// Simple key press trigger
	bool GetKeyDown(Keyboard::Key key) {
		if (Keyboard::isKeyPressed(key)) {		
			return true;
		}
		else {
			return false;
		}
	}
	// For single frame
	bool GetKeyPressed(Keyboard::Key key, double &delay){
		if (Keyboard::isKeyPressed(key) && delay >= 2) {
			delay = 0;
			return true;
		}
		else {
			return false;
		}
	}
	// Get key held down
	bool GetKeyHeld(Keyboard::Key key) {
		if (Keyboard::isKeyPressed(key)) {
			return true;
		}
		else {
			return false;
		}
	}
	// Simple mouse click trigger
	bool GetMouseDown(Mouse::Button button) {
		if (Mouse::isButtonPressed(button)) {
			return true;
		}
		else {
			return false;
		}
	}
	// For single frame
	bool GetMousePressed(Mouse::Button button, double &delay) {
		if (Mouse::isButtonPressed(button) && delay >= 2) {
			delay = 0;
			return true;
		}
		else {
			return false;
		}
	}
	// Returns direction value from axis, 0 = horizontal, 1 = verticals
	float GetAxisValue(int axis) {
		return 0.0;
	}

	bool MouseInWindow(Vector2i &mousePos) {
		if (mousePos.x >= Engine::GetWindow().getPosition().x &&
			mousePos.x <= (Engine::GetWindow().getPosition().x + Engine::getWindowSize().x) &&
			mousePos.y >= Engine::GetWindow().getPosition().y &&
			mousePos.y <= (Engine::GetWindow().getPosition().y + Engine::getWindowSize().y))
		{
			return true;
		}
		else {
			return false;
		}
	}

	// WHY DOESN'T THIS WORK?????????

	/*Vector2i GetMousePos(Window &window) 
		return Mouse::getPosition((Window&)window);
	}*/
};

namespace controls 
{
	void CheckCameraInput(View &view, float &zoom, double dt) 
	{
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
}