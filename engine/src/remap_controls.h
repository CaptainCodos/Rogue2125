#pragma once

#include <SFML/Graphics.hpp>

class PlayerControls {
private:
	static std::map<std::string, sf::Keyboard::Key> keyTable;

public:
	static void Initialise();
	static sf::Keyboard::Key GetKey(std::string key);
	static void SetKey(std::string key, sf::Keyboard::Key newKey);

	static unsigned int GetControllerButton(std::string input);
	static void SetControllerButton(std::string input, unsigned int button);
};