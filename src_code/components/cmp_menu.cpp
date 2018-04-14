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

	_btn_options.reset();
	_btn_options = new_button("Options");
	buttons.push_back(_btn_options);

	// Set buttons position
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 300.0f + (i * 350), Engine::getWindowSize().y / 2));
		buttons[i]->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(buttons[i]->getPosition().x, buttons[i]->getPosition().y - 8.0f));
	}
}

void MenuComponent::update(double dt)
{
	if (_btn_start_game->get_components<ButtonComponent>()[0]->clicked()) {
		counter++;
		Engine::ChangeScene(&gameplay);
	}

	if (_btn_options->get_components<ButtonComponent>()[0]->clicked()) {
		Engine::ChangeScene(&settings);
	}
}

void MenuComponent::render()
{
}
