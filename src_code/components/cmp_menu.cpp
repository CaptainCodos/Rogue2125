#include "cmp_menu.h"
#include "../buttons.h"
#include "cmp_button.h"
#include "engine.h"
#include "../game.h"
#include "system_player_controls.h"
#include "ecm.h"

using namespace std;
using namespace sf;
using namespace Input;

extern int counter;
double menuDelay = 0;

MenuComponent::MenuComponent(Entity* p) : Component(p) {
	LoadButtons();
}

void MenuComponent::LoadButtons() {
	// Button loading
	buttons.clear();
	_btn_start_game.reset();
	_btn_start_game = new_button("Start");
	buttons.push_back(_btn_start_game);

	_btn_settings.reset();
	_btn_settings = new_button("Options");
	buttons.push_back(_btn_settings);

	_btn_highscores.reset();
	_btn_highscores = new_button("Highscores");
	buttons.push_back(_btn_highscores);

	_btn_quit.reset();
	_btn_quit = new_button("Quit");
	_btn_quit->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 50.0f, Engine::getWindowSize().y / 2 + 100.0f));
	_btn_quit->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(_btn_quit->getPosition().x, _btn_quit->getPosition().y - 8.0f));
	buttons.push_back(_btn_quit);

	// Set buttons position
	for (int i = 0; i < buttons.size() - 1; i++) {
		buttons[i]->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 300.0f + (i * 350), Engine::getWindowSize().y / 2));
		buttons[i]->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(buttons[i]->getPosition().x, buttons[i]->getPosition().y - 8.0f));
	}
}

void MenuComponent::update(double dt)
{
	menuDelay += dt;

	if (_btn_start_game->get_components<ButtonComponent>()[0]->clicked(menuDelay))
	{
		counter++;
		Engine::ChangeScene(&gameplay, "gameplay");
	} else if (_btn_settings->get_components<ButtonComponent>()[0]->clicked(menuDelay))
	{
		Engine::ChangeScene(&settings, "settings");
	} else if (_btn_highscores->get_components<ButtonComponent>()[0]->clicked(menuDelay))
	{
		Engine::ChangeScene(&highscores, "highscores");
	} else if (_btn_quit->get_components<ButtonComponent>()[0]->clicked(menuDelay))
	{
		Engine::GetWindow().close();
	}
}

void MenuComponent::render()
{
}
