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
bool fullscreen = false;
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

		auto resHeader = makeEntity();
		auto rH = txt->addComponent<TextComponent>(
			"Resolution Options");
		rH->SetPos(Vector2f(Engine::getWindowSize().x / 2 - 120.0f, Engine::getWindowSize().y / 2 + 105.0f));

		btn_settings.reset();
		btn_settings = new_button("Back to Menu");
		btn_settings->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 50.0f, Engine::getWindowSize().y / 2 + 350.0f));
		btn_settings->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_settings->getPosition().x, btn_settings->getPosition().y - 8.0f));

		btn_fullscreen.reset();
		btn_fullscreen = new_button("Fullscreen");
		btn_fullscreen->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 130.0f, Engine::getWindowSize().y / 2 - 200.0f));
		btn_fullscreen->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_fullscreen->getPosition().x, btn_fullscreen->getPosition().y - 8.0f));

		btn_windowed.reset();
		btn_windowed = new_button("Windowed");
		btn_windowed->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 230.0f, Engine::getWindowSize().y / 2 - 200.0f));
		btn_windowed->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_windowed->getPosition().x, btn_windowed->getPosition().y - 8.0f));

		btn_res_one.reset();
		btn_res_one = new_button("Res: 1920x1080");
		btn_res_one->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 450.0f, Engine::getWindowSize().y / 2 + 175.0f));
		btn_res_one->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_res_one->getPosition().x, btn_res_one->getPosition().y - 8.0f));

		btn_res_two.reset();
		btn_res_two = new_button("Res: 1600x900");
		btn_res_two->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 50.0f, Engine::getWindowSize().y / 2 + 175.0f));
		btn_res_two->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_res_two->getPosition().x, btn_res_two->getPosition().y - 8.0f));

		btn_res_three.reset();
		btn_res_three = new_button("Res: 1024x768");
		btn_res_three->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 350.0f, Engine::getWindowSize().y / 2 + 175.0f));
		btn_res_three->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_res_three->getPosition().x, btn_res_three->getPosition().y - 8.0f));
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
	else if (btn_fullscreen->get_components<ButtonComponent>()[0]->clicked(settingsDelay)) 
	{
		fullscreen = true;
		Engine::GetWindow().create(sf::VideoMode(Engine::getWindowSize().x, Engine::getWindowSize().y, 32), "Rogue2125", sf::Style::Fullscreen);
	}
	else if (btn_windowed->get_components<ButtonComponent>()[0]->clicked(settingsDelay)) 
	{
		fullscreen = false;
		Engine::GetWindow().create(sf::VideoMode(Engine::getWindowSize().x, Engine::getWindowSize().y, 32), "Rogue2125", sf::Style::Resize);
	}
	else if (btn_res_one->get_components<ButtonComponent>()[0]->clicked(settingsDelay)) 
	{
		if (fullscreen == true) {
			Engine::GetWindow().create(sf::VideoMode(1920, 1080, 32), "Rogue2125", sf::Style::Fullscreen);
		}
		else {
			Engine::GetWindow().create(sf::VideoMode(1920, 1080, 32), "Rogue2125", sf::Style::Resize);
		}
	}
	else if (btn_res_two->get_components<ButtonComponent>()[0]->clicked(settingsDelay)) 
	{

	}
	else if (btn_res_three->get_components<ButtonComponent>()[0]->clicked(settingsDelay)) 
	{

	}

	Scene::Update(dt);
}