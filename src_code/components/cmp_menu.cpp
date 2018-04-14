#include "cmp_menu.h"
#include "../buttons.h"
#include "cmp_button.h"
#include "engine.h"
#include "../game.h"

using namespace std;
using namespace sf;

extern int counter;

MenuComponent::MenuComponent(Entity* p) : Component(p) {
	LoadButtons();
}

void MenuComponent::LoadButtons() {
	// Button loading
	buttons.clear();
	_btn_start_game.reset();
	_btn_start_game = new_button("Start");
	buttons.push_back(_btn_start_game);

	// Set buttons position
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 300.0f, Engine::getWindowSize().y / 2));
	}
}

void MenuComponent::update(double dt)
{
	if (_btn_start_game->get_components<ButtonComponent>()[0]->clicked()) {
		counter++;
		Engine::ChangeScene(&gameplay);
	}
}

void MenuComponent::render()
{
}
