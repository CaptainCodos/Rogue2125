#include "player_controls.h"

using namespace std;
using namespace sf;

map<std::string, Keyboard::Key> PlayerControls::keyTable;

void PlayerControls::Initialise() {
	PlayerControls::SetKey("Exit", Keyboard::Escape);
}

Keyboard::Key PlayerControls::GetKey(string key) {
	auto _key = keyTable.find(key);

	if (_key != keyTable.end()) {
		return _key->second;
	}
	else {
		throw invalid_argument("Key not found!");
	}
}

void PlayerControls::SetKey(string key, Keyboard::Key newKey) {
	keyTable[key] = newKey;
}

unsigned int PlayerControls::GetControllerButton(std::string input)
{
	return 0;
}

void PlayerControls::SetControllerButton(std::string input, unsigned int button)
{
}
