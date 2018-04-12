#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "engine.h"
#include "system_player_controls.h"

using namespace std;
using namespace sf;

// Simple key press trigger
bool Input::GetKeyDown(Keyboard::Key key) {
	Engine::GetWindow().setKeyRepeatEnabled(true);
	if (Keyboard::isKeyPressed(key)) {
		return true;
	}
}
// For single frame
bool Input::GetKeyPressed(Keyboard::Key key) {
	Engine::GetWindow().setKeyRepeatEnabled(false);
	if (Keyboard::isKeyPressed(key)) {
		return true;
	}
}
// Get key held down
bool Input::GetKeyHeld(Keyboard::Key key) {
	Engine::GetWindow().setKeyRepeatEnabled(true);
	if (Keyboard::isKeyPressed(key)) {
		return true;
	}
}
// Simple mouse click trigger
bool Input::GetMouseDown(Mouse::Button button) {
	Engine::GetWindow().setKeyRepeatEnabled(true);
	if (Mouse::isButtonPressed(button)) {
		return true;
	}
}
// For single frame
bool Input::GetMousePressed(Mouse::Button button) {
	Engine::GetWindow().setKeyRepeatEnabled(false);
	return false;
}
// Returns direction value from axis, 0 = horizontal, 1 = verticals
float Input::GetAxisValue(int axis)
{
	float val = 0.0f;

	switch (axis)
	{
	case 0:
		if (Input::GetKeyDown(Keyboard::A))
			val -= 1.0f;
		if (Input::GetKeyDown(Keyboard::D))
			val += 1.0f;
		break;
	case 1:
		if (Input::GetKeyDown(Keyboard::S))
			val += 1.0f;
		if (Input::GetKeyDown(Keyboard::W))
			val -= 1.0f;
		break;
	}

	return val;
}

bool Input::MouseInWindow()
{
	Vector2u size = Engine::getWindowSize();
	Vector2i pos = Input::GetMouseWindowPos();
	
	return (0 <= pos.x && pos.x < size.x) && (0 <= pos.y && pos.y < size.y);
}

Vector2i Input::GetMouseWindowPos()
{
	return Mouse::getPosition(Engine::GetWindow());
}

Vector2i Input::GetMouseRelativeToPos(Vector2i pos)
{
	Vector2i mScreen = Input::GetMouseWindowPos();
	return mScreen - pos;
}

void controls::CheckCameraInput(View &view, float &zoom, double dt)
{
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

void controls::GetMouseClick() {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		cout << "\r" << "Left Click Pressed." << endl;
	}
}

void controls::GetMousePos() {
	cout << "\r" << Input::GetMouseRelativeToPos(Vector2i(800, 450)) << std::flush;
}