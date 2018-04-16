#include "scene_pause.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void PauseScene::Load()
{

	cout << "Pause Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");

	}
	setLoaded(true);
}

void PauseScene::Update(const double& dt) {
	// cout << "Pause Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&menu, "menu");
	}

	Scene::Update(dt);
}