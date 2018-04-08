#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "ecm.h"

namespace Input
{
	static Keyboard currKeyboard;
	static Keyboard oldKeyboard;

	static Mouse currMouse;
	static Mouse oldMouse;

	bool GetKeyDown(Keyboard::Key key);		// Simple key press trigger
	bool GetKeyPressed(Keyboard::Key key);	// For single frame
	bool GetKeyHeld(Keyboard::Key key);		// Get key held down

	bool GetMouseDown(Mouse::Button button);	// Simple mouse click trigger
	bool GetMousePressed(Mouse::Button button);	// For single frame

	float GetAxisValue(int axis);	// Returns direction value from axis, 0 = horizontal, 1 = vertical

	void UpdateStatesBegin();
	void UpdateStatesEnd();
};

class System_Player_Controls : public Component {
protected:
	float speed;
	
public:
	explicit System_Player_Controls(Entity* p);
	System_Player_Controls() = delete;
};