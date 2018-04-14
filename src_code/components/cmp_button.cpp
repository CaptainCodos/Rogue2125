#include "cmp_button.h"
#include "system_player_controls.h"
#include "engine.h"
#include <SFML/Window/Mouse.hpp>

using namespace std;
using namespace sf;
using namespace Input;

ButtonComponent::ButtonComponent(Entity* p, shared_ptr<TextComponent> text, shared_ptr<ShapeComponent> shape) : _btnShape(shape), _btnText(text), Component(p) {

}

void ButtonComponent::update(double dt) {
	if (_btnShape->getShape().getGlobalBounds().contains(Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow())))) {
		_btnShape->getShape().setFillColor(Color(0, 255, 0, 255));
	}
	else {
		_btnShape->getShape().setFillColor(Color(255, 0, 0, 255));
	}
}

void ButtonComponent::render()
{

}

bool ButtonComponent::clicked(double delay) {
	if (_btnShape->getShape().getGlobalBounds().contains(Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow())))) {
		if (Input::GetMousePressed(Mouse::Left, delay) == true) {
			return true;
		}
	}
	return false;
}