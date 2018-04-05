#include "scene_settings.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void SettingsScene::Load()
{

	cout << "Settings Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");

	}
	setLoaded(true);
}

void SettingsScene::Update(const double& dt) {
	// cout << "Settings Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}