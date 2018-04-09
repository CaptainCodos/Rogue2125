//#include "remap_controls.h"
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//map<std::string, Keyboard::Key> PlayerControls::keyTable;
//
//void PlayerControls::Initialise() {
//	PlayerControls::SetKey("Exit", Keyboard::Escape);
//	PlayerControls::SetKey("Up", Keyboard::W);
//	PlayerControls::SetKey("Down", Keyboard::S);
//	PlayerControls::SetKey("Left", Keyboard::A);
//	PlayerControls::SetKey("Right", Keyboard::D);
//	PlayerControls::SetKey("Inventory", Keyboard::U);
//}
//
//Keyboard::Key PlayerControls::GetKey(string key) {
//	auto _key = keyTable.find(key);
//
//	if (_key != keyTable.end()) {
//		return _key->second;
//	}
//	else {
//		throw invalid_argument("Key not found!");
//	}
//}
//
//void PlayerControls::SetKey(string key, Keyboard::Key newKey) {
//	keyTable[key] = newKey;
//}
//
//unsigned int PlayerControls::GetControllerButton(string input)
//{
//	return 0;
//}
//
//void PlayerControls::SetControllerButton(string input, unsigned int button)
//{
//}
