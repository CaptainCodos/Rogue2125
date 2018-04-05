#include "scene_highscores.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void HighscoresScene::Load()
{

	cout << "Highscores Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");

	}
	setLoaded(true);
}

void HighscoresScene::Update(const double& dt) {
	// cout << "Highscores Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}