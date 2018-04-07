#include "system_player_controls.h"
#include "remap_controls.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

namespace Controls {

	Vector2f dir = { 0, 0 };

	void CheckForKey() {
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
		if (Keyboard::isKeyPressed(PlayerControls::GetKey("Inventory"))) {
			// Inventory/Player sceen logic here
		}
	}
}

System_Player_Controls::System_Player_Controls(Entity *p) : Component(p) {
	speed = 50.0f;
}