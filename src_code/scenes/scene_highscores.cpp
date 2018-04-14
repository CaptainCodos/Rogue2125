#include "scene_highscores.h"
#include "../buttons.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_highscores;

void HighscoresScene::Load()
{

	cout << "Highscores Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Highscores");
		t->SetPos(Vector2f(Engine::getWindowSize().x / 2 - 70.0f, Engine::getWindowSize().y / 2 - 350.f));

		btn_highscores.reset();
		btn_highscores = new_button("Back to Menu");
		btn_highscores->setPosition(Vector2f(Engine::getWindowSize().x / 2 + 50.0f, Engine::getWindowSize().y / 2 + 350.0f));
		btn_highscores->get_components<TextComponent>()[0]->SetPos(sf::Vector2f(btn_highscores->getPosition().x, btn_highscores->getPosition().y - 8.0f));
	}
	setLoaded(true);
}

void HighscoresScene::Update(const double& dt) {
	// cout << "Highscores Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (btn_highscores->get_components<ButtonComponent>()[0]->clicked())
	{
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}