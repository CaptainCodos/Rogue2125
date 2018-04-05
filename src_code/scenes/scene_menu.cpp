#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() 
{
	
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");
		
		auto tm = makeEntity();
		auto tmC = tm->addComponent<TileMapComponent>(txrMgr, 0);
	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	  Engine::ChangeScene(&gameplay);
  }

  Scene::Update(dt);
}
