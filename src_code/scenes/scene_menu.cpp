#include "scene_gameplay.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load()
{
	cout << "Gameplay Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");

	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	// cout << "Gameplay Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&gameplay);
	}

	Scene::Update(dt);
}
