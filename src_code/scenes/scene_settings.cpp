#include "scene_settings.h"
#include "../buttons.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_settings;
shared_ptr<Entity> btn_fullscreen;
shared_ptr<Entity> btn_windowed;
shared_ptr<Entity> btn_res_one;
shared_ptr<Entity> btn_res_two;
shared_ptr<Entity> btn_res_three;
double settingsDelay = 0;

void SettingsScene::Load()
{
	cout << "Settings Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Settings");
		t->SetPos(Vector2f(Engine::getWindowSize().x / 2 - 20.0f, Engine::getWindowSize().y / 2 - 350.f));

		auto displayHeader = makeEntity();
		auto dH = txt->addComponent<TextComponent>(
			"Window Options");
		dH->SetPos(Vector2f(Engine::getWindowSize().x / 2 - 80.0f, Engine::getWindowSize().y / 2 - 270.0f));

		btn_fullscreen.reset();
		btn_fullscreen = new_button("Fullscreen");
		btn_fullscreen->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 130.0f, Engine::getWindowSize().y / 2 - 200.0f));
		btn_fullscreen->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_fullscreen->getPosition().x, btn_fullscreen->getPosition().y - 8.0f));

		btn_windowed.reset();
		btn_windowed = new_button("Windowed");
		btn_windowed->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 230.0f, Engine::getWindowSize().y / 2 - 200.0f));
		btn_windowed->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_windowed->getPosition().x, btn_windowed->getPosition().y - 8.0f));

		btn_settings.reset();
		btn_settings = new_button("Back to Menu");
		btn_settings->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 50.0f, Engine::getWindowSize().y / 2 + 350.0f));
		btn_settings->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_settings->getPosition().x, btn_settings->getPosition().y - 8.0f));
	}
	setLoaded(true);
}

void SettingsScene::Update(const double& dt) {
	// cout << "Settings Update "<<dt<<"\n";

	settingsDelay += dt;

	txrMgr->UpdateAnims(dt);

	if (btn_settings->get_components<ButtonComponent>()[0]->clicked(settingsDelay))
	{
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}