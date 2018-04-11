#include "cmp_button.h"
#include "engine.h"
#include <SFML/Window/Mouse.hpp>

using namespace std;
using namespace sf;

ButtonComponent::ButtonComponent(Entity* p, shared_ptr<TextComponent> t, shared_ptr<ShapeComponent> s) : Component(p) {

}

void ButtonComponent::update(double dt) {
	if (_btnShape->getShape().getGlobalBounds().contains(Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow())))) {
		_btnShape->getShape().setFillColor(Color(0, 255, 0, 255));
	}
	else {
		_btnShape->getShape().setFillColor(Color(255, 0, 0, 255));
	}
}

bool ButtonComponent::clicked() {
	if (_btnShape->getShape().getGlobalBounds().contains(Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow())))) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			return true;
		}
	}
	return false;
}