#include "cmp_controls.h"
#include "../player_controls.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

void ControlsComponent::update(double dt) {
	const auto pos = _parent->getPosition();
	float _speed = speed;
	Vector2f dir = { 0, 0 };

	if (Keyboard::isKeyPressed(PlayerControls::GetKey("Up"))) {
		dir.y += 1.5f;
	}
	if (Keyboard::isKeyPressed(PlayerControls::GetKey("Down"))) {
		dir.y -= 1.5f;
	}
	if (Keyboard::isKeyPressed(PlayerControls::GetKey("Left"))) {
		dir.x -= 1.5f;
	}
	if (Keyboard::isKeyPressed(PlayerControls::GetKey("Right"))) {
		dir.x += 1.5f;
	}
}

ControlsComponent::ControlsComponent(Entity *p) : Component(p) {
	speed = 50.0f;
}